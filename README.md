# Computer Graphics Project
 mesh->oggetti
 overlay -> menù
 gubo -> ambiente

## PER AGGIUNGERE UN OGGETTO:
``` c++
 Model<VertexMesh> MObject; //solo se non è presente già una copia di quell'oggetto
 DescriptorSet DSObject;
 Texture TObject; //solo se non è presente già una copia di quell'oggetto
 MeshUniformBlock uboObject;

 uniformBlocksInPool = aumenta di 1;
 texturesInPool = aumenta di 1; //solo se non è presente già una copia di quell'oggetto
 setsInPool = aumenta di 1;

 //se l'oggetto ha una mesh:
 MBody.init(this,   &VMesh, "Models/ObjectMesh.obj", OBJ);
 //se invece vuoi farlo a mano come per gli assignment:
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

 //posizionare l'oggetto nel mondo:
 World = ruotare e traslare a piacimento;
 uboObject.amb = 1.0f; uboObject.gamma = 180.0f; uboObject.sColor = glm::vec3(1.0f);
 uboObject.mvpMat = ViewPrj * World;
 uboObject.mMat = World;
 uboObject.nMat = glm::inverse(glm::transpose(World));
 DSObject.map(currentImage, &uboObject, sizeof(uboObject), 0);
```

## PER CREARE UN NUOVO SHADER:
``` c++
 Pipeline PMeshNew;
 PMeshNew.init(this, &VMesh, "shaders/MeshVert.spv", "shaders/MeshNewFrag.spv", {&DSLGubo, &DSLMesh});

 //lo shader MeshNewFrag.spv deve essere compilato a partire da uno shader MeshNew.frag
 //che deve essere il copia-incolla di Mesh.frag a cui va cambiata la BDRF function

 PMeshNew.create();
 PMeshNew.cleanup();
 PMeshNew.destroy();

 //gli oggetti che vogliono avere il nuovo shader devono avere la pipeline nuova AL POSTO DELLA VECCHIA:
 DSObject.bind(commandBuffer, PNewMesh, 1, currentImage);

 PMesh.bind(commandBuffer);
```
- per cambiare dinamicamente la pipeline, basta fare uno switch-case nella populateCommandBuffer (vedi A12.cpp riga 329)
- poi, quando viene cambiata scena (es. si preme spazio): RebuildPipeline(); (vedi A12.cpp riga 411)

