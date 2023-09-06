// This has been adapted from the Vulkan tutorial
#include "Starter.hpp"
#include "TextMaker.hpp"

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



//function to create mesh
void createSphereMesh(std::vector<VertexMesh>& vDef, std::vector<uint32_t>& vIdx);

// MAIN ! 
class Project : public BaseProject {
	protected:
	//text
	std::vector<SingleText> levelStatus = {
		{1, {"", "", "", ""}, 0, 0},
		{1, {"Coins collected: 0/5", "", "", ""}, 0, 0},
		{1, {"Coins collected: 1/5", "", "", ""}, 0, 0},
		{1, {"Coins collected: 2/5", "", "", ""}, 0, 0},
		{1, {"Coins collected: 3/5", "", "", ""}, 0, 0},
		{1, {"Coins collected: 4/5", "", "", ""}, 0, 0}
	};
	int curText;

	//number of elements for each object
	//level one
	static const int n_ground = 9;
	//level two
	static const int n_wood = 25;
	static const int n_water = 24;
	static const int n_small_water = 44;
	static const int n_log = 7;
	static const int n_coin = 5;
	static const int n_cloud1 = 5;
	static const int n_cloud2 = 5;
	static const int n_cloud3 = 5;
	static const int n_bridge = 5;
	static const int n_lily = 1;
	static const int n_tot_assets = n_ground + n_water + n_small_water + n_log + n_wood +
									n_coin + n_cloud1 + n_cloud2 + n_cloud3 + n_bridge + n_lily;

	// Current aspect ratio (used by the callback that resized the window
	float Ar;

	// Descriptor Layouts ["classes" of what will be passed to the shaders]
	//overlay -> triggers
	//mesh -> objects
	//gubo -> environment
	DescriptorSetLayout DSLGubo, DSLMesh, DSLOverlay, DSLskyBox;

	// Vertex formats
	VertexDescriptor VMesh, VOverlay;

	//text
	TextMaker txt;

	// Pipelines [Shader couples]
	Pipeline PMesh, POverlay, PskyBox;

	// Models, textures and Descriptors (values assigned to the uniforms)
	// Please note that Model objects depends on the corresponding vertex structure
	Model<VertexMesh> MBody, MMars, MskyBox, MGround, MWater, MSmallWater, MLog, MCoin, MCloud1, MCloud2, MCloud3, MBridge, MLily, MWood;
	Model<VertexOverlay> MGameOver, MSplash, MMenu;
	DescriptorSet DSGubo, DSBody, DSGameOver, DSSplash, DSMars, DSskyBox, DSMenu;
	DescriptorSet DSGround[n_ground], DSWater[n_water], DSSmallWater[n_small_water], DSLog[n_log], DSCoin[n_coin],
				  DSCloud1[n_cloud1], DSCloud2[n_cloud2], DSCloud3[n_cloud3], DSBridge[n_bridge], DSLily[n_lily], DSWood[n_wood];
	Texture TAssets, TGameOver, TSplash, TMars, TskyBox, TMenu;
	
	// C++ storage for uniform variables
	MeshUniformBlock uboBody, uboMars, uboAssets;
	SkyboxUniformBufferObject uboSky;
	GlobalUniformBlock gubo;
	OverlayUniformBlock uboGameOver, uboSplash, uboMenu;

	// Other application parameters

	//camera settings
	float CamH, CamRadius, CamPitch, CamYaw;
	float yaw;
	glm::mat3 SkyBoxDir = glm::mat3(1.0f);

	//current player position
	glm::vec3 bodyPos;
	glm::vec3 fixedBodyPos;

	//handle cursor
	GLFWcursor* cursor;
	double xpos, ypos;

	//variable handling the game logic
	int gameState;
	int currentLevel;
	bool MoveCam;
	int coinsCollected;

	//world matrix for the objects
	glm::mat4 GroundWM[n_ground];
	glm::mat4 WaterWM[n_water];
	glm::mat4 SmallWaterWM[n_small_water];
	glm::mat4 LogWM[n_log];
	glm::mat4 CoinWM[n_coin];
	glm::mat4 Cloud1WM[n_cloud1];
	glm::mat4 Cloud2WM[n_cloud2];
	glm::mat4 Cloud3WM[n_cloud3];
	glm::mat4 BridgeWM[n_bridge];
	glm::mat4 LilyWM[n_lily];
	glm::mat4 WoodWM[n_wood];

	//vectors with the distances to check for the collision
	const glm::vec3 collision_log = glm::vec3(1.0f, 0.3f, 0.5f);
	const glm::vec3 collision_log_rotated = glm::vec3(0.5f, 0.3f, 1.0f);
	const glm::vec3 collision_coin = glm::vec3(0.7f, 1.0f, 0.7f);
	const glm::vec3 collision_water = glm::vec3(4.0f, 4.0f, 4.0f);
	const glm::vec3 collision_small_water = glm::vec3(2.0f, 2.0f, 2.0f);

	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 1200;
		windowHeight = 800;
		windowTitle = "Project";
    	windowResizable = GLFW_TRUE;
		initialBackgroundColor = {0.0f, 0.005f, 0.01f, 1.0f};
		
		// Descriptor pool sizes
		uniformBlocksInPool = 8 + n_tot_assets; //contare gli ubo
		texturesInPool = 7 + n_tot_assets; //contare le texture nei ds.init
		setsInPool = 8 + n_tot_assets; //contare i descriptor set
		
		Ar = (float)windowWidth / (float)windowHeight;
	}
	
	// What to do when the window changes size
	void onWindowResize(int w, int h) {
		Ar = (float)w / (float)h;
		windowWidth = w;
		windowHeight = h;
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
		MBody.init(this, &VMesh, "Models/slime.obj", OBJ);
		MskyBox.init(this, &VMesh, "Models/SkyBoxCube.obj", OBJ);
		MGround.init(this, &VMesh, "Models/ground_grass_8.obj", OBJ);
		MWood.init(this, &VMesh, "Models/ground_wood_4.obj", OBJ);
		MWater.init(this, &VMesh, "Models/water_4.obj", OBJ);
		MSmallWater.init(this, &VMesh, "Models/water_4.obj", OBJ);
		MLog.init(this, &VMesh, "Models/wall_spiked_logs.obj", OBJ);
		MCoin.init(this, &VMesh, "Models/coin.obj", OBJ);
		MCloud1.init(this, &VMesh, "Models/cloud_1.obj", OBJ);
		MCloud2.init(this, &VMesh, "Models/cloud_2.obj", OBJ);
		MCloud3.init(this, &VMesh, "Models/cloud_3.obj", OBJ);
		MBridge.init(this, &VMesh, "Models/bridge_1.obj", OBJ);
		MLily.init(this, &VMesh, "Models/lilypad.obj", OBJ);

		createSphereMesh(MMars.vertices, MMars.indices);
		MMars.initMesh(this, &VMesh);

		
		// Creates a mesh with direct enumeration of vertices and indices
		MGameOver.vertices = { {{-1.0f, -1.0f}, {0.0f, 0.0f}}, {{-1.0f, 1.0f}, {0.0f,1.0f}},
						 {{ 1.0f, -1.0f}, {1.0f,0.0f}}, {{ 1.0f, 1.0f}, {1.0f,1.0f}} };
		MGameOver.indices = {0, 1, 2,    1, 2, 3};
		MGameOver.initMesh(this, &VOverlay);
		
		// Creates a mesh with direct enumeration of vertices and indices
		MSplash.vertices = {{{-1.0f, -1.0f}, {0.0f, 0.0f}}, {{-1.0f, 1.0f}, {0.0f,1.0f}},
						 {{ 1.0f, -1.0f}, {1.0f,0.0f}}, {{ 1.0f, 1.0f}, {1.0f,1.0f}}};
		MSplash.indices = {0, 1, 2,    1, 2, 3};
		MSplash.initMesh(this, &VOverlay);

		// Creates a mesh with direct enumeration of vertices and indices
		MMenu.vertices = { {{-1.0f, -1.0f}, {0.0f, 0.0f}}, {{-1.0f, 1.0f}, {0.0f,1.0f}},
						 {{ 1.0f, -1.0f}, {1.0f,0.0f}}, {{ 1.0f, 1.0f}, {1.0f,1.0f}} };
		MMenu.indices = { 0, 1, 2,    1, 2, 3 };
		MMenu.initMesh(this, &VOverlay);
		
		// Create the textures
		// The second parameter is the file name
		TAssets.init(this,   "textures/palette.png");
		TGameOver.init(this, "textures/gameover.png");
		TSplash.init(this, "textures/SplashScreen.png");
		TMars.init(this, "textures/2k_mars.jpg");
		TMenu.init(this, "textures/menu.png");

		txt.init(this, &levelStatus);

		const char* T2fn[] = { "textures/sky2/bkg1_right.png", "textures/sky2/bkg1_left.png",
							  "textures/sky2/bkg1_top.png",   "textures/sky2/bkg1_bot.png",
							  "textures/sky2/bkg1_front.png", "textures/sky2/bkg1_back.png" };
		TskyBox.initCubic(this, T2fn);
		
		// Init local variables
		CamH = 1.0f;
		CamPitch = glm::radians(15.f);
		CamYaw = glm::radians(0.f);
		yaw = 0.0f;
		gameState = 0;
		currentLevel = 0;
		MoveCam = false;
		curText = 0;
		coinsCollected = 0;

		place_wood();
		place_ground();
		place_water();
		place_logs();
		place_coins_first_level();
		//place_coins_second_level();
		place_small_water();
		place_lily();
		place_bridges();
		place_clouds();
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
					{1, TEXTURE, 0, &TAssets}
				});
		DSskyBox.init(this, &DSLskyBox, {
					{0, UNIFORM, sizeof(SkyboxUniformBufferObject), nullptr},
					{1, TEXTURE, 0, &TskyBox}
			});
		DSMars.init(this, &DSLMesh, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMars}
				});
		DSGameOver.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TGameOver}
				});
		DSSplash.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TSplash}
				});
		DSMenu.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMenu}
			});
		DSGubo.init(this, &DSLGubo, {
					{0, UNIFORM, sizeof(GlobalUniformBlock), nullptr}
				});

		for (int i = 0; i < n_ground; i++) {
			DSGround[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_water; i++) {
			DSWater[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_small_water; i++) {
			DSSmallWater[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_log; i++) {
			DSLog[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_coin; i++) {
			DSCoin[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_bridge; i++) {
			DSBridge[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_lily; i++) {
			DSLily[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_cloud1; i++) {
			DSCloud1[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_cloud2; i++) {
			DSCloud2[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_cloud3; i++) {
			DSCloud3[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}
		for (int i = 0; i < n_wood; i++) {
			DSWood[i].init(this, &DSLMesh, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TAssets}
				});
		}

		txt.pipelinesAndDescriptorSetsInit();
		
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
		DSMars.cleanup();
		DSMenu.cleanup();
		for (int i = 0; i < n_ground; i++) DSGround[i].cleanup();
		for (int i = 0; i < n_water; i++) DSWater[i].cleanup();
		for (int i = 0; i < n_small_water; i++) DSSmallWater[i].cleanup();
		for (int i = 0; i < n_log; i++) DSLog[i].cleanup();
		for (int i = 0; i < n_coin; i++) DSCoin[i].cleanup();
		for (int i = 0; i < n_cloud1; i++) DSCloud1[i].cleanup();
		for (int i = 0; i < n_cloud2; i++) DSCloud2[i].cleanup();
		for (int i = 0; i < n_cloud3; i++) DSCloud3[i].cleanup();
		for (int i = 0; i < n_bridge; i++) DSBridge[i].cleanup();
		for (int i = 0; i < n_lily; i++) DSLily[i].cleanup();
		for (int i = 0; i < n_wood; i++) DSWood[i].cleanup();
		DSGameOver.cleanup();
		DSSplash.cleanup();
		DSGubo.cleanup();
		DSskyBox.cleanup();

		txt.pipelinesAndDescriptorSetsCleanup();
	}

	// Here you destroy all the Models, Texture and Desc. Set Layouts you created!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	// You also have to destroy the pipelines: since they need to be rebuilt, they have two different
	// methods: .cleanup() recreates them, while .destroy() delete them completely
	void localCleanup() {
		// Cleanup textures
		TAssets.cleanup();
		TGameOver.cleanup();
		TSplash.cleanup();
		TMars.cleanup();
		TskyBox.cleanup();
		TMenu.cleanup();
		
		// Cleanup models
		MBody.cleanup();
		MGameOver.cleanup();
		MSplash.cleanup();
		MMars.cleanup();
		MskyBox.cleanup();
		MMenu.cleanup();
		MGround.cleanup();
		MWater.cleanup();
		MSmallWater.cleanup();
		MLog.cleanup();
		MCoin.cleanup();
		MCloud1.cleanup();
		MCloud2.cleanup();
		MCloud3.cleanup();
		MBridge.cleanup();
		MLily.cleanup();
		MWood.cleanup();
		
		// Cleanup descriptor set layouts
		DSLMesh.cleanup();
		DSLOverlay.cleanup();
		DSLskyBox.cleanup();
		DSLGubo.cleanup();

		txt.localCleanup();
		
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

		switch (currentLevel) {
		case 1:
			MMars.bind(commandBuffer);
			DSMars.bind(commandBuffer, PMesh, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MMars.indices.size()), 1, 0, 0, 0);

			MGround.bind(commandBuffer);
			for (int i = 0; i < n_ground; i++) {
				DSGround[i].bind(commandBuffer, PMesh, 1, currentImage); //attenti a metterlo vicino agli altri oggetti che usano la stessa pipeline
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MGround.indices.size()), 1, 0, 0, 0);
			}
			MLog.bind(commandBuffer);
			for (int i = 0; i < n_log; i++) {
				DSLog[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MLog.indices.size()), 1, 0, 0, 0);
			}

			MCoin.bind(commandBuffer);
			for (int i = 0; i < n_coin; i++) {
				DSCoin[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MCoin.indices.size()), 1, 0, 0, 0);
			}

			PskyBox.bind(commandBuffer);
			MskyBox.bind(commandBuffer);
			DSskyBox.bind(commandBuffer, PskyBox, 0, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MskyBox.indices.size()), 1, 0, 0, 0);
			break;
		case 2:
			MMars.bind(commandBuffer);
			DSMars.bind(commandBuffer, PMesh, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MMars.indices.size()), 1, 0, 0, 0);

			MWater.bind(commandBuffer);
			for (int i = 0; i < n_water; i++) {
				DSWater[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MWater.indices.size()), 1, 0, 0, 0);
			}

			MSmallWater.bind(commandBuffer);
			for (int i = 0; i < n_small_water; i++) {
				DSSmallWater[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MSmallWater.indices.size()), 1, 0, 0, 0);
			}

			MCloud1.bind(commandBuffer);
			for (int i = 0; i < n_cloud1; i++) {
				DSCloud1[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MCloud1.indices.size()), 1, 0, 0, 0);
			}

			MBridge.bind(commandBuffer);
			for (int i = 0; i < n_bridge; i++) {
				DSBridge[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MBridge.indices.size()), 1, 0, 0, 0);
			}

			MLily.bind(commandBuffer);
			for (int i = 0; i < n_lily; i++) {
				DSLily[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MLily.indices.size()), 1, 0, 0, 0);
			}

			MCloud2.bind(commandBuffer);
			for (int i = 0; i < n_cloud2; i++) {
				DSCloud2[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MCloud2.indices.size()), 1, 0, 0, 0);
			}

			MCloud3.bind(commandBuffer);
			for (int i = 0; i < n_cloud3; i++) {
				DSCloud3[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MCloud3.indices.size()), 1, 0, 0, 0);
			}

			MWood.bind(commandBuffer);
			for (int i = 0; i < n_wood; i++) {
				DSWood[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MWood.indices.size()), 1, 0, 0, 0);
			}

			MCoin.bind(commandBuffer);
			for (int i = 0; i < n_coin; i++) {
				DSCoin[i].bind(commandBuffer, PMesh, 1, currentImage);
				vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(MCoin.indices.size()), 1, 0, 0, 0);
			}

			PskyBox.bind(commandBuffer);
			MskyBox.bind(commandBuffer);
			DSskyBox.bind(commandBuffer, PskyBox, 0, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MskyBox.indices.size()), 1, 0, 0, 0);
			break;
		case 0: //splash screen
			POverlay.bind(commandBuffer);
			MSplash.bind(commandBuffer);
			DSSplash.bind(commandBuffer, POverlay, 0, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MSplash.indices.size()), 1, 0, 0, 0);
			break;
		case 3: //menu
			POverlay.bind(commandBuffer);
			MMenu.bind(commandBuffer);
			DSMenu.bind(commandBuffer, POverlay, 0, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MMenu.indices.size()), 1, 0, 0, 0);
			break;
		case 4: //gameover
			POverlay.bind(commandBuffer);
			MGameOver.bind(commandBuffer);
			DSGameOver.bind(commandBuffer, POverlay, 0, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MGameOver.indices.size()), 1, 0, 0, 0);
			break;
		}

		txt.populateCommandBuffer(commandBuffer, currentImage, curText);

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

		//handle key press debounce
		static float debounce = false;
		static int curDebounce = 0;

		// To debounce the pressing of the fire button, and start the event when the key is released
		static bool wasFire = false;
		bool handleFire = (wasFire && (!fire));
		wasFire = fire;

		//coin rotation speed
		const float coinSpeed = glm::radians(120.0f);
		static float coinAngle = 0.0f;

		//handle cursor
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);


		// Parameters
		// Camera FOV-y, Near Plane and Far Plane
		const float FOVy = glm::radians(90.0f);
		const float nearPlane = 0.1f;
		const float farPlane = 100.0f;
		const float rotSpeed = glm::radians(120.0f);
		const float movSpeed = 4.0f;

		// Camera Pitch limits
		const float minPitch = glm::radians(-8.75f);
		const float maxPitch = glm::radians(60.0f);
		float prev_pitch = CamPitch;

		//Current player angle
		static float fixedYaw = 0.0f;

		const float camDist = 2.0f;

		//handle collisions
		glm::vec3 tx = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1));
		glm::vec3 ty = glm::vec3(0, 1, 0);
		glm::vec3 tz = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1));
		glm::vec3 bodyCollider = glm::vec3(bodyPos + tx * movSpeed * m.x * deltaT +
			ty * movSpeed * m.y * deltaT +
			tz * movSpeed * m.z * deltaT);

		switch(gameState) {		// main state machine implementation
		  case 0: // initial state - show splash screen
			m = glm::vec3(0.0f);
			r = glm::vec3(0.0f);
			if(handleFire) {
				gameState = 1;
				currentLevel = 1;
				curText++;
				RebuildPipeline();
			}
			if (isInRectangle(0.352, 0.686, 0.674, 0.752)) {
				buttonPlayLevel(1, &debounce, &curDebounce, false);
			}
			else {
				cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
				glfwSetCursor(window, cursor);
			}
			break;
		  case 1: // level one
			// handle coin rotation
			coinAngle += coinSpeed * deltaT;

			//check collisions
			for (int i = 0; i < n_log; i++) {
				if (checkCollision(bodyCollider, bodyPos, glm::vec3(LogWM[i][3].x, LogWM[i][3].y, LogWM[i][3].z), collision_log)
					&& !MoveCam) {
					m = glm::vec3(0.0f);
					r = glm::vec3(0.0f);
					//std::cout << "COLLISION";
				}
			}
			break;
		  case 2: // level two
			// handle coin rotation
			coinAngle += coinSpeed * deltaT;

			//check collisions
			for (int i = 0; i < n_water; i++) {
				if (checkCollision(bodyCollider, bodyPos, glm::vec3(WaterWM[i][3].x, WaterWM[i][3].y, WaterWM[i][3].z), collision_water)
					&& !MoveCam) {
					m = glm::vec3(0.0f);
					r = glm::vec3(0.0f);
					reset_position();
					coinsCollected = 0;
					curText = 1;
					place_coins_second_level();
					RebuildPipeline();
					//std::cout << "COLLISION";
				}
			}

			for (int i = 0; i < n_small_water; i++) {
				if (checkCollision(bodyCollider, bodyPos, glm::vec3(SmallWaterWM[i][3].x, SmallWaterWM[i][3].y, SmallWaterWM[i][3].z), collision_small_water)
					&& !MoveCam) {
					m = glm::vec3(0.0f);
					r = glm::vec3(0.0f);
					reset_position();
					coinsCollected = 0;
					curText = 1;
					place_coins_second_level();
					RebuildPipeline();
					//std::cout << "COLLISION";
				}
			}
			break;
		  case 3: // pause menu
			m = glm::vec3(0.0f);
			r = glm::vec3(0.0f);

			//resume button
			if (isInRectangle( 0.341, 0.374, 0.657, 0.438)) {
				buttonPlayLevel(currentLevel, &debounce, &curDebounce, true);
			}
			//level one button
			else if (isInRectangle(0.341, 0.5194, 0.657, 0.5806)) {
				buttonPlayLevel(1, &debounce, &curDebounce, false);
			}
			//level two button
			else if (isInRectangle(0.341, 0.664, 0.657, 0.725)) {
				buttonPlayLevel(2, &debounce, &curDebounce, false);
			}
			//exit button
			else if (isInRectangle(0.341, 0.81, 0.657, 0.871)) {
				cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR); // GLFW_CROSSHAIR_CURSOR
				glfwSetCursor(window, cursor);
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
			}
			else {
				cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
				glfwSetCursor(window, cursor);
			}
			break;
		  case 4: //gameOver
			break;
		}
				
		if (gameState == 1 || gameState == 2) {
			for (int i = 0; i < n_coin; i++) {
				if (checkCollision(bodyCollider, bodyPos, glm::vec3(CoinWM[i][3].x, CoinWM[i][3].y, CoinWM[i][3].z), collision_coin) &&
					!MoveCam) {
					CoinWM[i] = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)), glm::vec3(10000.0f));
					coinsCollected++;
					if (coinsCollected == 5) {
						m = glm::vec3(0.0f);
						r = glm::vec3(0.0f);
						coinsCollected = 0;
						if (currentLevel == 1) {
							reset_position();
							gameState = 2;
							currentLevel = 2;
							curText = 1;
							place_coins_second_level();
						}
						else {
							reset_position();
							gameState = 4;
							currentLevel = 4;
							curText = 0;
						}
						RebuildPipeline();
					}
					else {
						curText = coinsCollected + 1;
						RebuildPipeline();
					}
					//std::cout << "COLLISION";
				}
			}
		}
		
		//update camera position and rotation
		CamRadius -= m.x * movSpeed * deltaT;
		CamPitch -= r.x * rotSpeed * deltaT;
		if (CamPitch > maxPitch || CamPitch < minPitch) CamPitch = prev_pitch;
		CamYaw += rotSpeed * r.z * deltaT;
		yaw -= r.y * rotSpeed * deltaT;
		
		handleCameraSwitch(&debounce, &curDebounce, &yaw, &fixedYaw);

		//handle enter key press
		if (glfwGetKey(window, GLFW_KEY_ENTER)) {
			debounce = true;
			curDebounce = GLFW_KEY_ENTER;
		}
		else {
			if ((curDebounce == GLFW_KEY_ENTER) && debounce) {
				debounce = false;
				curDebounce = 0;
				if (gameState == 0) {
					gameState = 1;
					currentLevel = 1;
					curText++;
					RebuildPipeline();
				}
				else if (gameState == 1 || gameState == 2 || gameState == 4) gameState = 3;
				else if (gameState == 3) gameState = currentLevel;
				curText = (gameState == 1 || gameState == 2) ? coinsCollected + 1 : 0;
				RebuildPipeline();
			}
		}
		
		
		

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
		glm::mat4 View = glm::lookAt(c, a, u);

		//Projection matrix
		glm::mat4 Prj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
		Prj[1][1] *= -1;
		glm::vec3 camTarget = glm::vec3(0, CamH, 0);
		glm::vec3 camPos =  camTarget +
							CamRadius * glm::vec3(cos(CamPitch) * sin(yaw),
							sin(CamPitch),
							cos(CamPitch) * cos(yaw));

		gubo.DlightDir = glm::normalize(glm::vec3(1, 2, 3));
		gubo.DlightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		gubo.AmbLightColor = glm::vec3(0.1f);
		gubo.eyePos = camPos;

		//View-projection matrix
		glm::mat4 ViewPrj = Prj * View;


		uboBody.amb = 1.0f; uboBody.gamma = 180.0f; uboBody.sColor = glm::vec3(1.0f);
		if (!MoveCam) {
			uboBody.mMat = World /** glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0,1,0))*/;
		}
		else {
			uboBody.mMat =  glm::translate(glm::mat4(1.0), glm::vec3(fixedBodyPos)) *
							glm::rotate(glm::mat4(1.0), fixedYaw, glm::vec3(0, 1, 0)) *
							glm::scale(glm::mat4(1.0), glm::vec3(1.0f));
		}
		uboBody.mvpMat = ViewPrj * uboBody.mMat;
		uboBody.nMat = glm::inverse(glm::transpose(uboBody.mMat));
		DSBody.map(currentImage, &uboBody, sizeof(uboBody), 0);

		
		uboSky.mMat = glm::translate(glm::mat4(1.0), glm::vec3(1.0f, -10.0f, 1.0f)) *
					  glm::scale(glm::mat4(1.0), glm::vec3(100.0f));
		uboSky.mvpMat = ViewPrj * uboSky.mMat;
		uboSky.nMat = glm::inverse(glm::transpose(uboSky.mMat));
		DSskyBox.map(currentImage, &uboSky, sizeof(uboSky), 0);

		World = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 2.5f, 0.0f));
		uboMars.amb = 1.0f; uboMars.gamma = 180.0f; uboMars.sColor = glm::vec3(1.0f);
		uboMars.mvpMat = ViewPrj * World;
		uboMars.mMat = World;
		uboMars.nMat = glm::inverse(glm::transpose(World));
		DSMars.map(currentImage, &uboMars, sizeof(uboMars), 0);

		if (gameState == 1) {
			for (int i = 0; i < n_ground; i++) {
				uboAssets.mMat = GroundWM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSGround[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
			for (int i = 0; i < n_log; i++) {
				uboAssets.mMat = LogWM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSLog[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
		}
		else if (gameState == 2) {
			for (int i = 0; i < n_wood; i++) {
				uboAssets.mMat = WoodWM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSWood[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
			for (int i = 0; i < n_water; i++) {
				uboAssets.mMat = WaterWM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSWater[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
			for (int i = 0; i < n_small_water; i++) {
				uboAssets.mMat = SmallWaterWM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSSmallWater[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
			for (int i = 0; i < n_bridge; i++) {
				uboAssets.mMat = BridgeWM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSBridge[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
			for (int i = 0; i < n_lily; i++) {
				uboAssets.mMat = LilyWM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSLily[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}

			for (int i = 0; i < n_cloud1; i++) {
				uboAssets.mMat = Cloud1WM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSCloud1[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}

			for (int i = 0; i < n_cloud2; i++) {
				uboAssets.mMat = Cloud2WM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSCloud2[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
			for (int i = 0; i < n_cloud3; i++) {
				uboAssets.mMat = Cloud3WM[i];
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSCloud3[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
		}
		if (gameState == 1 || gameState == 2) {
			for (int i = 0; i < n_coin; i++) {
				uboAssets.mMat = CoinWM[i] * glm::rotate(glm::mat4(1.0), coinAngle, glm::vec3(0, 1, 0));
				uboAssets.mvpMat = ViewPrj * uboAssets.mMat;
				uboAssets.nMat = glm::inverse(glm::transpose(uboAssets.mMat));
				DSCoin[i].map(currentImage, &uboAssets, sizeof(uboAssets), 0);
			}
		}
		
		/* map the uniform data block to the GPU */

		uboGameOver.visible = (gameState == 4) ? 1.0f : 0.0f;
		DSGameOver.map(currentImage, &uboGameOver, sizeof(uboGameOver), 0);

		uboSplash.visible = (gameState == 0) ? 1.0f : 0.0f;
		DSSplash.map(currentImage, &uboSplash, sizeof(uboSplash), 0);

		uboMenu.visible = (gameState == 3) ? 1.0f : 0.0f;
		DSMenu.map(currentImage, &uboMenu, sizeof(uboMenu), 0);
	}

	void buttonPlayLevel(int level, float *debounce, int *curDebounce, bool resume) {
		cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR); // GLFW_CROSSHAIR_CURSOR
		glfwSetCursor(window, cursor);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			*debounce = true;
			*curDebounce = GLFW_MOUSE_BUTTON_LEFT;
		}
		else {
			if ((*curDebounce == GLFW_MOUSE_BUTTON_LEFT) && *debounce) {
				*debounce = false;
				*curDebounce = 0;
				cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
				glfwSetCursor(window, cursor);
				gameState = level;
				currentLevel = level;
				if (!resume) {
					reset_position();
					coinsCollected = 0;
					if(level == 1) place_coins_first_level();
					if (level == 2) place_coins_second_level();
				}
				curText = (currentLevel==1 || currentLevel == 2) ? coinsCollected + 1 : 0;
				RebuildPipeline();
			}
		}
	}

	void reset_position() {
		bodyPos = glm::vec3(0.0f);
		CamPitch = glm::radians(15.f);
		CamYaw = glm::radians(0.0f);
		yaw = 0.0f;
	}

	bool isInRectangle(float x_left, float y_up, float x_right, float y_down) {
		float x = xpos / (float)windowWidth;
		float y = ypos / (float)windowHeight;
		return  x > x_left && x < x_right && y > y_up && y < y_down;
	}

	void handleCameraSwitch(float *debounce, int *curDebounce, float *yaw, float *fixedYaw) {
		if (glfwGetKey(window, GLFW_KEY_P) && !(gameState == 0 || gameState == 3)) {
			if (!*debounce) {
				*debounce = true;
				*curDebounce = GLFW_KEY_P;
				//std::cout << "Switch!  " << (MoveCam ? "Camera" : "Key") << "\n";
			}
		}
		else {
			if ((*curDebounce == GLFW_KEY_P) && *debounce) {
				*debounce = false;
				*curDebounce = 0;
				MoveCam = !MoveCam;
				if (MoveCam) {
					fixedBodyPos = bodyPos;
					*fixedYaw = *yaw;
				}
				else {
					bodyPos = fixedBodyPos;
					*yaw = *fixedYaw;
				}
				//std::cout << "Switch!  " << (MoveCam ? "Cam" : "K") << "\n";
			}
		}
	}

	bool checkCollision(const glm::vec3 box1, const glm::vec3 originalbox, const glm::vec3 box2, const glm::vec3 value) {
		return  abs(box1 - box2).x <= value.x &&
				abs(box1 - box2).y <= value.y &&
				abs(box1 - box2).z <= value.z &&
				sqrt(pow((box1 - box2).x, 2) + pow((box1 - box2).y, 2) + pow((box1 - box2).z, 2)) <=
				sqrt(pow((originalbox - box2).x, 2) + pow((originalbox - box2).y, 2) + pow((originalbox - box2).z, 2));
	}

	void place_wood() {
		WoodWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 0));
		WoodWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 1.0f)), glm::vec3(0, 0, -2));
		WoodWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, -4));
		WoodWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 0));
		WoodWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 0));
		WoodWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 8));
		WoodWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 8));
		WoodWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 4));
		WoodWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 4));
		WoodWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, -4));
		WoodWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, -8));
		WoodWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, -8));
		WoodWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 0));
		WoodWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 0));
		WoodWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 8));
		WoodWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, -8));
		WoodWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 8));
		WoodWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 8));
		WoodWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, -8));
		WoodWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, -4));
		WoodWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, -8));
		WoodWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, -4));
		WoodWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 4));
		WoodWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 4));
		WoodWM[24] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 4));
	}

	void place_ground() {
		GroundWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, 0));
		GroundWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, -8));
		GroundWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-8, 0, -8));
		GroundWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-8, 0, 0));
		GroundWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(8, 0, 0));
		GroundWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-8, 0, 8));
		GroundWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(8, 0, -8));
		GroundWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(8, 0, 8));
		GroundWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, 8));
	}

	void place_water() {
		WaterWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, -12));
		WaterWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, -8));
		WaterWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, -4));
		WaterWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 0));
		WaterWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 4));
		WaterWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 8));
		WaterWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 12));
		WaterWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, -12));
		WaterWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, -8));
		WaterWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, -4));
		WaterWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 0));
		WaterWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 4));
		WaterWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 8));
		WaterWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 12));
		WaterWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, -12));
		WaterWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, -12));
		WaterWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, -12));
		WaterWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, -12));
		WaterWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, -12));
		WaterWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 12));
		WaterWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 12));
		WaterWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 12));
		WaterWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 12));
		WaterWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 12));
	}

	void place_logs() {
		LogWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(5, 0.2, 0)) *
			glm::rotate(glm::mat4(1.0), 90.f, glm::vec3(0, 1, 0));
		LogWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(40, 0.2, -20));
		LogWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(39, 0.2, -20));
		LogWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-28, 0.2, 8)) *
			glm::rotate(glm::mat4(1.0), 90.f, glm::vec3(0, 1, 0));
		LogWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-28.8, 0.2, 7.5));
		LogWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12, 0.2, -8))
			* glm::rotate(glm::mat4(1.0), 45.f, glm::vec3(0, 1, 0));
		LogWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(5, 0.2, 18));
	}

	void place_coins_first_level() {
		CoinWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(5.7f, 0.7f, 0));
		CoinWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(39.5, 0.7, -21));
		CoinWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-28.7, 0.7, 8.2));
		CoinWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12.5, 0.7, -8.6));
		CoinWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(5.15, 0.7, 18.5));
	}

	void place_coins_second_level() {
		CoinWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0.7f, -14));
		CoinWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.7, -18));
		CoinWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.7, 2));
		CoinWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.7, 18));
		CoinWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.7, 18));
	}

	void place_small_water() {
		SmallWaterWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, -6));
		SmallWaterWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, -2));
		SmallWaterWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, 2));
		SmallWaterWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, 6));
		SmallWaterWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, -6));
		SmallWaterWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, -2));
		SmallWaterWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, 2));
		SmallWaterWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, 6));
		SmallWaterWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, -6));
		SmallWaterWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, -6));
		SmallWaterWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, 6));
		SmallWaterWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, -18));
		SmallWaterWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, -14));
		SmallWaterWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, -14));
		SmallWaterWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, -14));
		SmallWaterWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, -14));
		SmallWaterWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, -14));
		SmallWaterWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, -14));
		SmallWaterWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, -10));
		SmallWaterWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0.1, -10));
		SmallWaterWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, -2));
		SmallWaterWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 2));
		SmallWaterWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 6));
		SmallWaterWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 10));
		SmallWaterWM[24] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 14));
		SmallWaterWM[25] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 18));
		SmallWaterWM[26] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0.1, -2));
		SmallWaterWM[27] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, 6));
		SmallWaterWM[28] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, 14));
		SmallWaterWM[29] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, 14));
		SmallWaterWM[30] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, 14));
		SmallWaterWM[31] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, 14));
		SmallWaterWM[32] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, 14));
		SmallWaterWM[33] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, 14));
		SmallWaterWM[34] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, 18));
		SmallWaterWM[35] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, -6));
		SmallWaterWM[36] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, -2));
		SmallWaterWM[37] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, 2));
		SmallWaterWM[38] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, 6));
		SmallWaterWM[39] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, 6));
		SmallWaterWM[40] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 6));
		SmallWaterWM[41] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 10));
		SmallWaterWM[42] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 14));
		SmallWaterWM[43] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 18));
	}

	void place_lily() {
		LilyWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-8, 0.2, -8));
	}

	void place_bridges() {
		BridgeWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, 6));
		BridgeWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -10));
		BridgeWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(0, 0, -5));
		BridgeWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, 14));
		BridgeWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, 14));
	}

	void place_clouds() {
		Cloud1WM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(9.7f, 8.7f, 3));
		Cloud1WM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(30.5, 8.7, -11));
		Cloud1WM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-21.7, 8.7, 4.2));
		Cloud1WM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-7.5, 8.7, -0.6));
		Cloud1WM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(5.15, 8.7, 18.5));

		Cloud2WM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18.7f, 8.7f, 0));
		Cloud2WM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(24.5, 8.7, -21));
		Cloud2WM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18.7, 8.7, -14.2));
		Cloud2WM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2.5, 8.7, 15.6));
		Cloud2WM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(21.15, 8.7, 28.5));

		Cloud3WM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12.7f, 8.7f, 10));
		Cloud3WM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(39.5, 8.7, -1));
		Cloud3WM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-28.7, 8.7, 0.2));
		Cloud3WM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12.5, 8.7, 8.6));
		Cloud3WM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18.15, 8.7, 20.5));
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