// This has been adapted from the Vulkan tutorial
#include "Starter.hpp"

/* mesh->oggetti
 overlay -> menù
 gubo -> ambiente

 PER AGGIUNGERE UN OGGETTO:
 Model<VertexMesh> MObject; //solo se non è presente già una copia di quell'oggetto
 DescriptorSet DSObject;
 Texture TObject; //solo se non è presente già una copia di quell'oggetto
 MeshUniformBlock uboObject;

 uniformBlocksInPool = aumenta di 1;
 texturesInPool = aumenta di 1; //solo se non è presente già una copia di quell'oggetto
 setsInPool = aumenta di 1;

 se l'oggetto ha una mesh:
 MBody.init(this,   &VMesh, "Models/ObjectMesh.obj", OBJ);
 se invece vuoi farlo a mano come per gli assignment:
 MObject.vertices = *come negli assignment*
 MObject.indices = *come negli assignment*;
 MObject.initMesh(this, &VMesh);

 TObject.init(this,   "textures/ObjectTexture.png");
 DSObject.init(this, &DSLMesh, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TObject}
				});
 
 DSObject.cleanup();
 TObject.cleanup();
 MObject.cleanup();

 MObject.bind(commandBuffer);
 DSObject.bind(commandBuffer, PMesh, 1, currentImage); //attenti a metterlo vicino agli altri oggetti che usano la stessa pipeline
 vkCmdDrawIndexed(commandBuffer,
		static_cast<uint32_t>(MObject.indices.size()), 1, 0, 0, 0);

 posizionare l'oggetto nel mondo:
 World = ruotare e traslare a piacimento;
 uboObject.amb = 1.0f; uboObject.gamma = 180.0f; uboObject.sColor = glm::vec3(1.0f);
 uboObject.mvpMat = ViewPrj * World;
 uboObject.mMat = World;
 uboObject.nMat = glm::inverse(glm::transpose(World));
 DSObject.map(currentImage, &uboObject, sizeof(uboObject), 0);

 PER CREARE UN NUOVO SHADER:
 Pipeline PMeshNew;
 PMeshNew.init(this, &VMesh, "shaders/MeshVert.spv", "shaders/MeshNewFrag.spv", {&DSLGubo, &DSLMesh});

 lo shader MeshNewFrag.spv deve essere compilato a partire da uno shader MeshNew.frag
 che deve essere il copia-incolla di Mesh.frag a cui va cambiata la BDRF function

 PMeshNew.create();
 PMeshNew.cleanup();
 PMeshNew.destroy();

 gli oggetti che vogliono avere il nuovo shader devono avere la pipeline nuova AL POSTO DELLA VECCHIA:
 DSObject.bind(commandBuffer, PNewMesh, 1, currentImage);

 PMesh.bind(commandBuffer);

 per cambiare dinamicamente la pipeline, basta fare uno switch-case nella populateCommandBuffer (vedi A12.cpp riga 329)
 poi, quando viene cambiata scena (es. si preme spazio): RebuildPipeline(); (vedi A12.cpp riga 411)

 */

struct MeshUniformBlock {
	alignas(4) float amb;
	alignas(4) float gamma;
	alignas(16) glm::vec3 sColor;
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
};

struct OverlayUniformBlock {
	alignas(4) float visible;
};

struct GlobalUniformBlock {
	alignas(16) glm::vec3 DlightDir;
	alignas(16) glm::vec3 DlightColor;
	alignas(16) glm::vec3 AmbLightColor;
	alignas(16) glm::vec3 eyePos;
};

// The vertices data structures
struct VertexMesh {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

struct VertexOverlay {
	glm::vec2 pos;
	glm::vec2 UV;
};

struct SkyboxUniformBufferObject {
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
};

//functions (to be moved in separate files)
void createSphereMesh(std::vector<VertexMesh>& vDef, std::vector<uint32_t>& vIdx);


// MAIN ! 
class Project : public BaseProject {
	protected:

	// Current aspect ratio (used by the callback that resized the window
	float Ar;

	// Descriptor Layouts ["classes" of what will be passed to the shaders]
	//overlay -> triggers
	//mesh -> objects
	//gubo -> environment
	DescriptorSetLayout DSLGubo, DSLMesh, DSLOverlay, DSLskyBox;

	// Vertex formats
	VertexDescriptor VMesh, VOverlay;

	// Pipelines [Shader couples]
	Pipeline PMesh, POverlay, PskyBox;

	// Models, textures and Descriptors (values assigned to the uniforms)
	// Please note that Model objects depends on the corresponding vertex structure
	Model<VertexMesh> MBody, MHandle, MWheel, MMars, MskyBox;
	Model<VertexOverlay> MKey, MSplash;
	DescriptorSet DSGubo, DSBody, DSHandle, DSWheel1, DSWheel2, DSWheel3, DSKey, DSSplash, DSMars, DSskyBox;
	Texture TBody, THandle, TWheel, TKey, TSplash, TMars, TskyBox;
	
	// C++ storage for uniform variables
	MeshUniformBlock uboBody, uboHandle, uboWheel1, uboWheel2, uboWheel3, uboMars;
	SkyboxUniformBufferObject uboSky;
	GlobalUniformBlock gubo;
	OverlayUniformBlock uboKey, uboSplash;

	// Other application parameters
	float CamH, CamRadius, CamPitch, CamYaw;
	glm::mat3 SkyBoxDir = glm::mat3(1.0f);

	bool MoveCam = false;
	glm::vec3 bodyPos;
	glm::vec3 fixedBodyPos;
	glm::quat bodyRot;
	glm::vec3 bodyScale;
	glm::vec3 CamRadius2;

	int gameState;
	float HandleRot = 0.0;
	float Wheel1Rot = 0.0;
	float Wheel2Rot = 0.0;
	float Wheel3Rot = 0.0;

	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 600;
		windowTitle = "Project";
    	windowResizable = GLFW_TRUE;
		initialBackgroundColor = {0.0f, 0.005f, 0.01f, 1.0f};
		
		// Descriptor pool sizes
		uniformBlocksInPool = 10; //contare gli ubo (perché uno in più? è un bug mio?)
		texturesInPool = 9; //contare le texture nei ds.init
		setsInPool = 10; //contare i descriptor set
		
		Ar = (float)windowWidth / (float)windowHeight;
	}
	
	// What to do when the window changes size
	void onWindowResize(int w, int h) {
		Ar = (float)w / (float)h;
	}
	
	// Here you load and setup all your Vulkan Models and Texutures.
	// Here you also create your Descriptor set layouts and load the shaders for the pipelines
	void localInit() {
		// Descriptor Layouts [what will be passed to the shaders]
		DSLMesh.init(this, {
					// this array contains the bindings:
					// first  element : the binding number
					// second element : the type of element (buffer or texture)
					//                  using the corresponding Vulkan constant
					// third  element : the pipeline stage where it will be used
					//                  using the corresponding Vulkan constant
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
				});
				
		DSLOverlay.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
				});
				
		DSLGubo.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS}
				});
		DSLskyBox.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
				});

		// Vertex descriptors
		VMesh.init(this, {
				  // this array contains the bindings
				  // first  element : the binding number
				  // second element : the stride of this binging
				  // third  element : whether this parameter change per vertex or per instance
				  //                  using the corresponding Vulkan constant
				  {0, sizeof(VertexMesh), VK_VERTEX_INPUT_RATE_VERTEX}
				}, {
				  // this array contains the location
				  // first  element : the binding number
				  // second element : the location number
				  // third  element : the offset of this element in the memory record
				  // fourth element : the data type of the element
				  //                  using the corresponding Vulkan constant
				  // fifth  elmenet : the size in byte of the element
				  // sixth  element : a constant defining the element usage
				  //                   POSITION - a vec3 with the position
				  //                   NORMAL   - a vec3 with the normal vector
				  //                   UV       - a vec2 with a UV coordinate
				  //                   COLOR    - a vec4 with a RGBA color
				  //                   TANGENT  - a vec4 with the tangent vector
				  //                   OTHER    - anything else
				  //
				  // ***************** DOUBLE CHECK ********************
				  //    That the Vertex data structure you use in the "offsetoff" and
				  //	in the "sizeof" in the previous array, refers to the correct one,
				  //	if you have more than one vertex format!
				  // ***************************************************
				  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexMesh, pos),
				         sizeof(glm::vec3), POSITION},
				  {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexMesh, norm),
				         sizeof(glm::vec3), NORMAL},
				  {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexMesh, UV),
				         sizeof(glm::vec2), UV}
				});

		VOverlay.init(this, {
				  {0, sizeof(VertexOverlay), VK_VERTEX_INPUT_RATE_VERTEX}
				}, {
				  {0, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexOverlay, pos),
				         sizeof(glm::vec2), OTHER},
				  {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexOverlay, UV),
				         sizeof(glm::vec2), UV}
				});

		// Pipelines [Shader couples]
		// The second parameter is the pointer to the vertex definition
		// Third and fourth parameters are respectively the vertex and fragment shaders
		// The last array, is a vector of pointer to the layouts of the sets that will
		// be used in this pipeline. The first element will be set 0, and so on..
		PMesh.init(this, &VMesh, "shaders/MeshVert.spv", "shaders/MeshFrag.spv", {&DSLGubo, &DSLMesh});
		PMesh.setAdvancedFeatures(VK_COMPARE_OP_LESS, VK_POLYGON_MODE_FILL,
									VK_CULL_MODE_NONE, false);
		POverlay.init(this, &VOverlay, "shaders/OverlayVert.spv", "shaders/OverlayFrag.spv", {&DSLOverlay});
		POverlay.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
 								    VK_CULL_MODE_NONE, false);
		PskyBox.init(this, &VMesh, "shaders/SkyBoxVert.spv", "shaders/SkyBoxFrag.spv", { &DSLskyBox });
		PskyBox.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
			VK_CULL_MODE_BACK_BIT, false);

		// Models, textures and Descriptors (values assigned to the uniforms)

		// Create models
		// The second parameter is the pointer to the vertex definition for this model
		// The third parameter is the file name
		// The last is a constant specifying the file type: currently only OBJ or GLTF
		MBody.init(this,   &VMesh, "Models/SlotBody.obj", OBJ);
		MHandle.init(this, &VMesh, "Models/SlotHandle.obj", OBJ);
		MWheel.init(this,  &VMesh, "Models/SlotWheel.obj", OBJ);
		MskyBox.init(this, &VMesh, "Models/SkyBoxCube.obj", OBJ);

		createSphereMesh(MMars.vertices, MMars.indices);
		MMars.initMesh(this, &VMesh);

		
		// Creates a mesh with direct enumeration of vertices and indices
		MKey.vertices = {{{-0.8f, 0.6f}, {0.0f,0.0f}}, {{-0.8f, 0.95f}, {0.0f,1.0f}},
						 {{ 0.8f, 0.6f}, {1.0f,0.0f}}, {{ 0.8f, 0.95f}, {1.0f,1.0f}}};
		MKey.indices = {0, 1, 2,    1, 2, 3};
		MKey.initMesh(this, &VOverlay);
		
		// Creates a mesh with direct enumeration of vertices and indices
		MSplash.vertices = {{{-1.0f, -0.58559f}, {0.0102f, 0.0f}}, {{-1.0f, 0.58559f}, {0.0102f,0.85512f}},
						 {{ 1.0f,-0.58559f}, {1.0f,0.0f}}, {{ 1.0f, 0.58559f}, {1.0f,0.85512f}}};
		MSplash.indices = {0, 1, 2,    1, 2, 3};
		MSplash.initMesh(this, &VOverlay);
		
		// Create the textures
		// The second parameter is the file name
		TBody.init(this,   "textures/SlotBody.png");
		THandle.init(this, "textures/SlotHandle.png");
		TWheel.init(this,  "textures/SlotWheel.png");
		TKey.init(this,    "textures/PressSpace.png");
		TSplash.init(this, "textures/SplashScreen.png");
		TMars.init(this, "textures/2k_mars.jpg");

		const char* T2fn[] = { "textures/sky/bkg1_right.png", "textures/sky/bkg1_left.png",
							  "textures/sky/bkg1_top.png",   "textures/sky/bkg1_bot.png",
							  "textures/sky/bkg1_front.png", "textures/sky/bkg1_back.png" };
		TskyBox.initCubic(this, T2fn);
		
		// Init local variables
		CamH = 1.0f;
		//CamRadius = 3.0f;
		CamPitch = glm::radians(15.f);
		CamYaw = glm::radians(0.f);
		gameState = 0;
	}
	
	// Here you create your pipelines and Descriptor Sets!
	void pipelinesAndDescriptorSetsInit() {
		// This creates a new pipeline (with the current surface), using its shaders
		PMesh.create();
		POverlay.create();
		PskyBox.create();
		
		// Here you define the data set
		DSBody.init(this, &DSLMesh, {
		// the second parameter, is a pointer to the Uniform Set Layout of this set
		// the last parameter is an array, with one element per binding of the set.
		// first  elmenet : the binding number
		// second element : UNIFORM or TEXTURE (an enum) depending on the type
		// third  element : only for UNIFORMs, the size of the corresponding C++ object. For texture, just put 0
		// fourth element : only for TEXTUREs, the pointer to the corresponding texture object. For uniforms, use nullptr
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TBody}
				});
		DSHandle.init(this, &DSLMesh, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &THandle}
				});
		DSWheel1.init(this, &DSLMesh, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TWheel}
				});
		DSWheel2.init(this, &DSLMesh, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TWheel}
				});
		DSWheel3.init(this, &DSLMesh, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TWheel}
				});
		DSskyBox.init(this, &DSLskyBox, {
					{0, UNIFORM, sizeof(SkyboxUniformBufferObject), nullptr},
					{1, TEXTURE, 0, &TskyBox}
			});
		DSMars.init(this, &DSLMesh, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMars}
				});
		DSKey.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TKey}
				});
		DSSplash.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TSplash}
				});
		DSGubo.init(this, &DSLGubo, {
					{0, UNIFORM, sizeof(GlobalUniformBlock), nullptr}
				});
		
	}

	// Here you destroy your pipelines and Descriptor Sets!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	void pipelinesAndDescriptorSetsCleanup() {
		// Cleanup pipelines
		PMesh.cleanup();
		POverlay.cleanup();
		PskyBox.cleanup();

		// Cleanup datasets
		DSBody.cleanup();
		DSHandle.cleanup();
		DSWheel1.cleanup();
		DSWheel2.cleanup();
		DSWheel3.cleanup();
		DSMars.cleanup();

		DSKey.cleanup();
		DSSplash.cleanup();
		DSGubo.cleanup();
		DSskyBox.cleanup();
	}

	// Here you destroy all the Models, Texture and Desc. Set Layouts you created!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	// You also have to destroy the pipelines: since they need to be rebuilt, they have two different
	// methods: .cleanup() recreates them, while .destroy() delete them completely
	void localCleanup() {
		// Cleanup textures
		TBody.cleanup();
		THandle.cleanup();
		TWheel.cleanup();
		TKey.cleanup();
		TSplash.cleanup();
		TMars.cleanup();
		TskyBox.cleanup();
		
		// Cleanup models
		MBody.cleanup();
		MHandle.cleanup();
		MWheel.cleanup();
		MKey.cleanup();
		MSplash.cleanup();
		MMars.cleanup();
		MskyBox.cleanup();
		
		// Cleanup descriptor set layouts
		DSLMesh.cleanup();
		DSLOverlay.cleanup();
		DSLskyBox.cleanup();
		DSLGubo.cleanup();
		
		// Destroies the pipelines
		PMesh.destroy();		
		POverlay.destroy();
		PskyBox.destroy();
	}
	
	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures
	
	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
		// sets global uniforms (see below fro parameters explanation)
		DSGubo.bind(commandBuffer, PMesh, 0, currentImage);

		// binds the pipeline
		PMesh.bind(commandBuffer);
		// For a pipeline object, this command binds the corresponing pipeline to the command buffer passed in its parameter

		// binds the model
		MBody.bind(commandBuffer);
		// For a Model object, this command binds the corresponing index and vertex buffer
		// to the command buffer passed in its parameter
		
		// binds the data set
		DSBody.bind(commandBuffer, PMesh, 1, currentImage);
		// For a Dataset object, this command binds the corresponing dataset
		// to the command buffer and pipeline passed in its first and second parameters.
		// The third parameter is the number of the set being bound
		// As described in the Vulkan tutorial, a different dataset is required for each image in the swap chain.
		// This is done automatically in file Starter.hpp, however the command here needs also the index
		// of the current image in the swap chain, passed in its last parameter
					
		// record the drawing command in the command buffer
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MBody.indices.size()), 1, 0, 0, 0);
		// the second parameter is the number of indexes to be drawn. For a Model object,
		// this can be retrieved with the .indices.size() method.

		MHandle.bind(commandBuffer);
		DSHandle.bind(commandBuffer, PMesh, 1, currentImage);
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MHandle.indices.size()), 1, 0, 0, 0);

		MWheel.bind(commandBuffer);
		DSWheel1.bind(commandBuffer, PMesh, 1, currentImage);
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MWheel.indices.size()), 1, 0, 0, 0);
		DSWheel2.bind(commandBuffer, PMesh, 1, currentImage);
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MWheel.indices.size()), 1, 0, 0, 0);
		DSWheel3.bind(commandBuffer, PMesh, 1, currentImage);
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MWheel.indices.size()), 1, 0, 0, 0);
		MMars.bind(commandBuffer);
		DSMars.bind(commandBuffer, PMesh, 1, currentImage);
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MMars.indices.size()), 1, 0, 0, 0);

		//aggiungere qui nuovi oggetti


		PskyBox.bind(commandBuffer);
		MskyBox.bind(commandBuffer);
		DSskyBox.bind(commandBuffer, PskyBox, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(MskyBox.indices.size()), 1, 0, 0, 0);
				
		POverlay.bind(commandBuffer);
		MKey.bind(commandBuffer);
		DSKey.bind(commandBuffer, POverlay, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MKey.indices.size()), 1, 0, 0, 0);

		MSplash.bind(commandBuffer);
		DSSplash.bind(commandBuffer, POverlay, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MSplash.indices.size()), 1, 0, 0, 0);

	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		// Standard procedure to quit when the ESC key is pressed
		if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
		// Integration with the timers and the controllers
		float deltaT;
		glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
		bool fire = false;
		getSixAxis(deltaT, m, r, fire);

		static float debounce = false;
		static int curDebounce = 0;
		// getSixAxis() is defined in Starter.hpp in the base class.
		// It fills the float point variable passed in its first parameter with the time
		// since the last call to the procedure.
		// It fills vec3 in the second parameters, with three values in the -1,1 range corresponding
		// to motion (with left stick of the gamepad, or ASWD + RF keys on the keyboard)
		// It fills vec3 in the third parameters, with three values in the -1,1 range corresponding
		// to motion (with right stick of the gamepad, or Arrow keys + QE keys on the keyboard, or mouse)
		// If fills the last boolean variable with true if fire has been pressed:
		//          SPACE on the keyboard, A or B button on the Gamepad, Right mouse button

		// To debounce the pressing of the fire button, and start the event when the key is released
		static bool wasFire = false;
		bool handleFire = (wasFire && (!fire));
		wasFire = fire;
		
		// Parameters: wheels and handle speed and range
		const float HandleSpeed = glm::radians(90.0f);
		const float HandleRange = glm::radians(45.0f);
		const float WheelSpeed = glm::radians(180.0f);
		const float SymExtent = glm::radians(15.0f);	// size of one symbol on the wheel in angle rad.
		// static variables for current angles
		static float HandleRot = 0.0;
		static float Wheel1Rot = 0.0;
		static float Wheel2Rot = 0.0;
		static float Wheel3Rot = 0.0;
		static float TargetRot = 0.0;	// Target rotation

//std::cout << gameState << "\n";	
		switch(gameState) {		// main state machine implementation
		  case 0: // initial state - show splash screen
			if(handleFire) {
				gameState = 1;	// jump to the wait key state
			}
			break;
		  case 1: // wait key state
			if(handleFire) {
				gameState = 2;	// jump to the moving handle state
			}
			break;
		  case 2: // handle moving down state
			HandleRot += HandleSpeed * deltaT;
			Wheel1Rot += WheelSpeed * deltaT;
			Wheel2Rot += WheelSpeed * deltaT;
			Wheel3Rot += WheelSpeed * deltaT;
			if(HandleRot > HandleRange) {	// when limit is reached, jump the handle moving up state
				gameState = 3;
				HandleRot = HandleRange;
			}
			break;
		  case 3: // handle moving up state
			HandleRot -= HandleSpeed * deltaT;
			Wheel1Rot += WheelSpeed * deltaT;
			Wheel2Rot += WheelSpeed * deltaT;
			Wheel3Rot += WheelSpeed * deltaT;
			if(HandleRot < 0.0f) {	// when limit is reached, jump the 3 wheels spinning state
				gameState = 4;
				HandleRot = 0.0f;
				TargetRot = Wheel1Rot + (10 + (rand() % 11)) * SymExtent;
			}
			break;
		  case 4: // 3 wheels spinning state
			Wheel1Rot += WheelSpeed * deltaT;
			Wheel2Rot += WheelSpeed * deltaT;
			Wheel3Rot += WheelSpeed * deltaT;
//std::cout << Wheel1Rot << " --- " << TargetRot << "\n";
			if(Wheel1Rot >= TargetRot) {	// When the target rotation is reached, jump to the next state
				gameState = 5;
				Wheel1Rot = round(TargetRot / SymExtent) * SymExtent; // quantize position
				TargetRot = Wheel2Rot + (10 + (rand() % 11)) * SymExtent;
			}
			break;
		  case 5: // 2 wheels spinning state
			Wheel2Rot += WheelSpeed * deltaT;
			Wheel3Rot += WheelSpeed * deltaT;
			if(Wheel2Rot >= TargetRot) {	// When the target rotation is reached, jump to the next state
				gameState = 6;
				Wheel2Rot = round(TargetRot / SymExtent) * SymExtent; // quantize position
				TargetRot = Wheel3Rot + (10 + (rand() % 11)) * SymExtent;
			}
			break;
		  case 6: // 1 wheels spinning state
			Wheel3Rot += WheelSpeed * deltaT;
			if(Wheel3Rot >= TargetRot) {	// When the target rotation is reached, jump to the next state
				gameState = 1;
				Wheel3Rot = round(TargetRot / SymExtent) * SymExtent; // quantize position
			}
			break;
		}
		
		// Parameters
		// Camera FOV-y, Near Plane and Far Plane
		const float FOVy = glm::radians(90.0f);
		const float nearPlane = 0.1f;
		const float farPlane = 100.0f;
		const float rotSpeed = glm::radians(120.0f);
		const float movSpeed = 2.0f;

		// Camera Pitch limits
		const float minPitch = glm::radians(-8.75f);
		const float maxPitch = glm::radians(60.0f);
		float prev_pitch = CamPitch;

		//Current player angle
		static float yaw = 0.0f;
		static float fixedYaw = 0.0f;
		
		const float camDist = 2.0f;
		
		CamRadius -= m.x * movSpeed * deltaT;
		CamPitch -= r.x * rotSpeed * deltaT;
		if (CamPitch > maxPitch || CamPitch < minPitch) CamPitch = prev_pitch;
		CamYaw += rotSpeed * r.z * deltaT;
		yaw -= r.y * rotSpeed * deltaT;

		if (glfwGetKey(window, GLFW_KEY_P)) {
			if (!debounce) {
				debounce = true;
				curDebounce = GLFW_KEY_P;
				MoveCam = !MoveCam;
				if(MoveCam) {
					fixedBodyPos = bodyPos;
					fixedYaw = yaw;
				}
				else {
					bodyPos = fixedBodyPos;
					yaw = fixedYaw;
				}
				std::cout << "Switch!  " << (MoveCam ? "Camera" : "Key") << "\n";
			}
		}
		else {
			if ((curDebounce == GLFW_KEY_P) && debounce) {
				debounce = false;
				curDebounce = 0;
				std::cout << "Switch!  " << (MoveCam ? "Cam" : "K") << "\n";
			}
		}
		
		
		//Projection matrix
		glm::mat4 Prj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
		Prj[1][1] *= -1;
		glm::vec3 camTarget = glm::vec3(0,CamH,0);
		glm::vec3 camPos    = camTarget +
							  CamRadius2 * glm::vec3(cos(CamPitch) * sin(yaw),
													sin(CamPitch),
													cos(CamPitch) * cos(yaw));

		gubo.DlightDir = glm::normalize(glm::vec3(1, 2, 3));
		gubo.DlightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		gubo.AmbLightColor = glm::vec3(0.1f);
		gubo.eyePos = camPos;

		// Writes value to the GPU
		DSGubo.map(currentImage, &gubo, sizeof(gubo), 0);
		// the .map() method of a DataSet object, requires the current image of the swap chain as first parameter
		// the second parameter is the pointer to the C++ data structure to transfer to the GPU
		// the third parameter is its size
		// the fourth parameter is the location inside the descriptor set of this uniform block

		//static glm::vec3 bodyPos;

		// The Walk model update procedure
		glm::vec3 ux = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1));
		glm::vec3 uy = glm::vec3(0, 1, 0);
		glm::vec3 uz = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1));
		
		bodyPos += ux * movSpeed * m.x * deltaT;
		bodyPos += uy * movSpeed * m.y * deltaT;
		bodyPos += uz * movSpeed * m.z * deltaT;

		glm::mat4 World =
			glm::translate(glm::mat4(1.0), glm::vec3(bodyPos)) *
			glm::rotate(glm::mat4(1.0), yaw, glm::vec3(0, 1, 0)) *
			glm::scale(glm::mat4(1.0), glm::vec3(1.0f));

		//View matrix
		//rotate the world matrix on y axis to make the player turn
		glm::mat4 World_y = World * glm::rotate(glm::mat4(1.0), CamYaw, glm::vec3(0, 1, 0));

		glm::vec3 c(World_y* glm::vec4(0, CamH + camDist * sin(CamPitch), camDist* cos(CamPitch), 1));
		glm::vec3 a(glm::vec3(World* glm::vec4(0, 0, 0, 1)) + glm::vec3(0, CamH, 0));
		static glm::vec3 u = glm::vec3(0, 1, 0);
		//u = movSpeed * m.x * deltaT; //MARIO GALAXY EFFECT!
		glm::mat4 View = glm::lookAt(c, a, u);

		//View-projection matrix
		glm::mat4 ViewPrj = Prj * View;

		//glm::mat4 World = glm::mat4(1);	
		uboBody.amb = 1.0f; uboBody.gamma = 180.0f; uboBody.sColor = glm::vec3(1.0f);
		if (!MoveCam) {
			uboBody.mMat = World /** glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0,1,0))*/;
		}
		else {
			uboBody.mMat =  glm::translate(glm::mat4(1.0), glm::vec3(fixedBodyPos)) *
							glm::rotate(glm::mat4(1.0), fixedYaw, glm::vec3(0, 1, 0)) *
							glm::scale(glm::mat4(1.0), glm::vec3(1.0f));;
		}
		uboBody.mvpMat = ViewPrj * uboBody.mMat;
		uboBody.nMat = glm::inverse(glm::transpose(uboBody.mMat));
		DSBody.map(currentImage, &uboBody, sizeof(uboBody), 0);

		//SKYBOX*********************************************************************************
		if (r.y != 0) {
			SkyBoxDir = glm::mat3(glm::rotate(glm::mat4(1.0f),
				-r.y * rotSpeed * deltaT,
				glm::vec3(SkyBoxDir[1])) * glm::mat4(SkyBoxDir));
		}
		if (r.x != 0 && CamPitch != prev_pitch) {
			SkyBoxDir = glm::mat3(glm::rotate(glm::mat4(1.0f),
				-r.x * deltaT * rotSpeed,
				glm::vec3(SkyBoxDir[0])) * glm::mat4(SkyBoxDir));
		}
		if (r.z != 0) {
			SkyBoxDir = glm::mat3(glm::rotate(glm::mat4(1.0f),
				deltaT * rotSpeed * r.z,
				glm::vec3(SkyBoxDir[1])) * glm::mat4(SkyBoxDir));
		}

		//glm::mat4 PrjSky = glm::perspective(glm::radians(45.0f), Ar, 0.1f, 50.0f); PrjSky[1][1] *= -1;
		uboSky.mMat = World;
		uboSky.mvpMat = Prj * glm::transpose(glm::mat4(SkyBoxDir));
		uboSky.nMat = glm::inverse(glm::transpose(uboSky.mMat));
		DSskyBox.map(currentImage, &uboSky, sizeof(uboSky), 0);
		//SKYBOX END*********************************************************************/
	
		World = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.3f,0.5f,-0.15f)),
							HandleRot, glm::vec3(1,0,0));
		uboHandle.amb = 1.0f; uboHandle.gamma = 180.0f; uboHandle.sColor = glm::vec3(1.0f);
		uboHandle.mMat = World;
		uboHandle.mvpMat = ViewPrj * uboHandle.mMat;
		uboHandle.nMat = glm::inverse(glm::transpose(uboHandle.mMat));
		DSHandle.map(currentImage, &uboHandle, sizeof(uboHandle), 0);
	
		World = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-0.15f,0.93f,-0.15f)),
							Wheel1Rot, glm::vec3(1,0,0));
		uboWheel1.amb = 1.0f; uboWheel1.gamma = 180.0f; uboWheel1.sColor = glm::vec3(1.0f);
		uboWheel1.mvpMat = Prj * View * World;
		uboWheel1.mMat = World;
		uboWheel1.nMat = glm::inverse(glm::transpose(World));
		DSWheel1.map(currentImage, &uboWheel1, sizeof(uboWheel1), 0);
	
		World = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.93f,-0.15f)),
							Wheel2Rot, glm::vec3(1,0,0));
		uboWheel2.amb = 1.0f; uboWheel2.gamma = 180.0f; uboWheel2.sColor = glm::vec3(1.0f);
		uboWheel2.mvpMat = Prj * View * World;
		uboWheel2.mMat = World;
		uboWheel2.nMat = glm::inverse(glm::transpose(World));
		DSWheel2.map(currentImage, &uboWheel2, sizeof(uboWheel2), 0);
	
		World = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.15f,0.93f,-0.15f)),
							Wheel3Rot, glm::vec3(1,0,0));
		uboWheel3.amb = 1.0f; uboWheel3.gamma = 180.0f; uboWheel3.sColor = glm::vec3(1.0f);
		uboWheel3.mvpMat = Prj * View * World;
		uboWheel3.mMat = World;
		uboWheel3.nMat = glm::inverse(glm::transpose(World));
		DSWheel3.map(currentImage, &uboWheel3, sizeof(uboWheel3), 0);

		World = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 2.5f, 0.0f));
		uboMars.amb = 1.0f; uboMars.gamma = 180.0f; uboMars.sColor = glm::vec3(1.0f);
		uboMars.mvpMat = ViewPrj * World;
		uboMars.mMat = World;
		uboMars.nMat = glm::inverse(glm::transpose(World));
		DSMars.map(currentImage, &uboMars, sizeof(uboMars), 0);

		/* map the uniform data block to the GPU */


		uboKey.visible = (gameState == 1) ? 1.0f : 0.0f;
		DSKey.map(currentImage, &uboKey, sizeof(uboKey), 0);

		uboSplash.visible = (gameState == 0) ? 1.0f : 0.0f;
		DSSplash.map(currentImage, &uboSplash, sizeof(uboSplash), 0);
	}	
};


// This is the main: probably you do not need to touch this!
int main() {
    Project app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void createSphereMesh(std::vector<VertexMesh>& vDef, std::vector<uint32_t>& vIdx) {
	// The primitive built here is a sphere of radius 1, centered in the origin, on which the Mars texture is applied seamless.

	/*
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	vDef.push_back({{0,0,0}, {0,0,1}, {0,0}});	// vertex 0 - Position, Normal and uv
	vDef.push_back({{1,0,0}, {0,0,1}, {1,0}});	// vertex 1 - Position and Normal
	vDef.push_back({{0,1,0}, {0,0,1}, {0,1}});	// vertex 2 - Position and Normal
	vDef.push_back({{1,1,0}, {0,0,1}, {1,1}});// vertex 3 - Position and Normal

	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	// First triangle
	vIdx.push_back(1); vIdx.push_back(2); vIdx.push_back(3);	// Second triangle
	*/

	float d = 2.0f;		//diameter of the sphere (guessed)
	int rings = 1000;		//resolution of the sphere along y axis (guessed)
	int slices = 1000;		//resolution of the sphere along x axis (guessed)

	float angle = 0.0f;
	float beta = glm::radians(180.0f / rings);
	float curr_y = d / 2 * cos(beta);
	float h = d / 2 - curr_y;	//height of current spherical cap
	float r = sqrt(h * (d - h));	// basis radius of current spherical cap

	float x_texture = 0.0f;
	float y_texture = 1.0f / rings;

	vDef.push_back({ {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} }); // vertex0 - top of the sphere
	for (int i = 0; i < rings - 1; i++) {
		for (int j = 0; j < slices; j++) {
			vDef.push_back({ {cos(angle) * r, curr_y, sin(angle) * r},
							{cos(angle), cos(beta), sin(angle)},
							{x_texture, y_texture} }); // vertexes on each ring
			if (i == 0) {
				if (j != 0) {
					vIdx.push_back(0); vIdx.push_back(j + 1); vIdx.push_back(j);
				}
				if (j == slices - 1) {
					vIdx.push_back(0); vIdx.push_back(j + 1); vIdx.push_back(1);
				}
			}
			if (i != 0) {
				if (j != 0) {
					vIdx.push_back(slices * i + j + 1); vIdx.push_back(slices * i + j); vIdx.push_back(slices * (i - 1) + j);
					vIdx.push_back(slices * i + j + 1); vIdx.push_back(slices * (i - 1) + j + 1); vIdx.push_back(slices * (i - 1) + j);
				}
				if (j == slices - 1) {
					vIdx.push_back(slices * i + j + 1); vIdx.push_back(slices * (i - 1) + j + 1); vIdx.push_back(slices * i + 1);
					vIdx.push_back(slices * (i - 1) + 1); vIdx.push_back(slices * (i - 1) + j + 1); vIdx.push_back(slices * i + 1);
				}
			}
			angle += glm::radians(360.0f / slices);
			x_texture += 1.0f / slices;
		}
		angle = 0.0f;
		beta += glm::radians(180.0f / rings);
		curr_y = d / 2 * cos(beta);
		h = beta > glm::radians(90.0f) ? d / 2 + curr_y : d / 2 - curr_y;
		r = sqrt(h * (d - h));
		x_texture = 0.0f;
		y_texture += 1.0f / rings;
	}

	vDef.push_back({ {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} });	// bottom of the sphere
	for (int j = 1; j < slices; j++) {
		vIdx.push_back(slices * (rings - 1) + 1); vIdx.push_back(slices * (rings - 2) + j + 1); vIdx.push_back(slices * (rings - 2) + j);
	}
	vIdx.push_back(slices * (rings - 1) + 1); vIdx.push_back(slices * (rings - 1)); vIdx.push_back(slices * (rings - 2) + 1);
}