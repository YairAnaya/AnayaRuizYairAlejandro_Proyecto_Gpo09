// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
#include "Texture.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void MovimientoDeMano( );
void AbrirRegalo( );
void MoverAlmohada( );
void animacion( );
void animacion2();

// Camera
Camera camera( glm::vec3( 40.0f, 20.0f, 10.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
//Nuevas variables para las animaciones
int estadoMano = 0;
float grados = 0.0;
float mano = 0.0;
float avaAlmo = -9.30;
float rotAlmo = 0.0;
float piano = 0.0;
bool ActivaMano = false;
bool ActivaRegalo = false;
bool ActivaAlmohada = false;

//*********************KEYFRAMES************************

//Variables Regalo
float regaloX = -8.2, regaloZ = 0.0;
//Variables Piano
float rotTB1 = 0.0, rotTB2 = 0.0, rotTB3 = 0.0, rotTN1 = 0.0, rotTN2 = 0.0, rotTN3 = 0.0;
//Variables regalo 
int i_max_steps = 100;
int i_curr_steps = 0;
bool play_regalo = false;
#define NumFrames 9
//Variables piano
int i_max_steps2 = 100;
int i_curr_steps2 = 0;
bool play_piano = false;
#define NumFrames2 13

//Regalo
typedef struct _frame
{
    //Variables para GUARDAR Key Frames
    //Regalo
    float posRX;
    float posRZ;
    float inc_posRX;
    float inc_posRZ;
  
}FRAME;

//Piano
typedef struct frame_piano
{
    //Variables para GUARDAR Key Frames
    //piano
    float posTB1;
    float posTB2;
    float posTB3;
    float posTN1;
    float posTN2;
    float posTN3;
    float inc_posTB1;
    float inc_posTB2;
    float inc_posTB3;
    float inc_posTN1;
    float inc_posTN2;
    float inc_posTN3;

}FRAME_Piano;

//Regalo
FRAME KeyFrame[NumFrames];
int FrameIndex = NumFrames;			
int playIndex = 0;
//Piano
FRAME_Piano KeyFrame2[NumFrames2];
int FrameIndex2 = NumFrames2;
int playIndex2 = 0;

//Regalo
void saveFrame(void)
{
    KeyFrame[0].posRX = regaloX;
    KeyFrame[0].posRZ = regaloZ;
   
    KeyFrame[1].posRX = -7.2;
    KeyFrame[1].posRZ = 1.0;

    KeyFrame[2].posRX = -6.2;
    KeyFrame[2].posRZ = 0.0;

    KeyFrame[3].posRX = -5.2;
    KeyFrame[3].posRZ = 1.0;

    KeyFrame[4].posRX = -4.2;
    KeyFrame[4].posRZ = 0.0;

    KeyFrame[5].posRX = -5.2;
    KeyFrame[5].posRZ = 1.0;

    KeyFrame[6].posRX = -6.2;
    KeyFrame[6].posRZ = 0.0;

    KeyFrame[7].posRX = -7.2;
    KeyFrame[7].posRZ = 1.0;

    KeyFrame[8].posRX = -8.2;
    KeyFrame[8].posRZ = 0.0;
 
}


//Piano
void saveFrame2(void)
{
    KeyFrame2[0].posTB1 = rotTB1;
    KeyFrame2[0].posTB2 = rotTB2;
    KeyFrame2[0].posTB3 = rotTB3;
    KeyFrame2[0].posTN1 = rotTN1;
    KeyFrame2[0].posTN2 = rotTN2;
    KeyFrame2[0].posTN3 = rotTN3;

    KeyFrame2[1].posTB1 = -5.0;
    KeyFrame2[1].posTB3 = -5.0;
    KeyFrame2[1].posTN1 = -5.0;
    KeyFrame2[1].posTN3 = -5.0;

    KeyFrame2[2].posTB1 = 0.0;
    KeyFrame2[2].posTB3 = 0.0;
    KeyFrame2[2].posTB2 = -5.0;
    KeyFrame2[2].posTN2 = -5.0;
    KeyFrame2[2].posTN1 = 0.0;
    KeyFrame2[2].posTN3 = 0.0;

    KeyFrame2[3].posTB2 = 0.0;
    KeyFrame2[3].posTN2 = 0.0;
    KeyFrame2[3].posTB1 = -5.0;
    KeyFrame2[3].posTN1 = -5.0;
    KeyFrame2[3].posTN3 = -5.0;

    KeyFrame2[4].posTB1 = 0.0;
    KeyFrame2[4].posTN1 = 0.0;
    KeyFrame2[4].posTN3 = 0.0;

    KeyFrame2[5].posTB1 = -5.0;
    KeyFrame2[5].posTB2 = -5.0;
    KeyFrame2[5].posTB3 = -5.0;
    KeyFrame2[5].posTN1 = -5.0;
    KeyFrame2[5].posTN2 = -5.0;
    KeyFrame2[5].posTN3 = -5.0;

    KeyFrame2[6].posTB1 = 0.0;
    KeyFrame2[6].posTB2 = 0.0;
    KeyFrame2[6].posTB3 = 0.0;
    KeyFrame2[6].posTN1 = 0.0;
    KeyFrame2[6].posTN2 = 0.0;
    KeyFrame2[6].posTN3 = 0.0;

    KeyFrame2[7].posTB1 = -5.0;
    KeyFrame2[7].posTB3 = -5.0;
    KeyFrame2[7].posTN1 = -5.0;
    KeyFrame2[7].posTN3 = -5.0;

    KeyFrame2[8].posTB1 = 0.0;
    KeyFrame2[8].posTB3 = 0.0;
    KeyFrame2[8].posTB2 = -5.0;
    KeyFrame2[8].posTN2 = -5.0;
    KeyFrame2[8].posTN1 = 0.0;
    KeyFrame2[8].posTN3 = 0.0;

    KeyFrame2[9].posTB2 = 0.0;
    KeyFrame2[9].posTN2 = 0.0;
    KeyFrame2[9].posTB1 = -5.0;
    KeyFrame2[9].posTN1 = -5.0;
    KeyFrame2[9].posTN3 = -5.0;

    KeyFrame2[10].posTB1 = 0.0;
    KeyFrame2[10].posTN1 = 0.0;
    KeyFrame2[10].posTN3 = 0.0;

    KeyFrame2[11].posTB1 = -5.0;
    KeyFrame2[11].posTB2 = -5.0;
    KeyFrame2[11].posTB3 = -5.0;
    KeyFrame2[11].posTN1 = -5.0;
    KeyFrame2[11].posTN2 = -5.0;
    KeyFrame2[11].posTN3 = -5.0;

    KeyFrame2[12].posTB1 = 0.0;
    KeyFrame2[12].posTB2 = 0.0;
    KeyFrame2[12].posTB3 = 0.0;
    KeyFrame2[12].posTN1 = 0.0;
    KeyFrame2[12].posTN2 = 0.0;
    KeyFrame2[12].posTN3 = 0.0;


}
//regalo
void resetElements(void)
{
    regaloX = KeyFrame[0].posRX;
    regaloZ = KeyFrame[0].posRZ;

}

//piano
void resetElements2(void)
{
    rotTB1 = KeyFrame2[0].posTB1;
    rotTB2 = KeyFrame2[0].posTB2;
    rotTB3 = KeyFrame2[0].posTB3;
    rotTN1 = KeyFrame2[0].posTN1;
    rotTN2 = KeyFrame2[0].posTN2;
    rotTN3 = KeyFrame2[0].posTN3;

}

//Regalo
void interpolation(void)
{

    KeyFrame[playIndex].inc_posRX = (KeyFrame[playIndex + 1].posRX- KeyFrame[playIndex].posRX) / i_max_steps;
    KeyFrame[playIndex].inc_posRZ= (KeyFrame[playIndex + 1].posRZ- KeyFrame[playIndex].posRZ) / i_max_steps;
}

//Piano
void interpolation2(void)
{

    KeyFrame2[playIndex2].inc_posTB1 = (KeyFrame2[playIndex2 + 1].posTB1 - KeyFrame2[playIndex2].posTB1) / i_max_steps2;
    KeyFrame2[playIndex2].inc_posTB2 = (KeyFrame2[playIndex2 + 1].posTB2 - KeyFrame2[playIndex2].posTB2) / i_max_steps2;
    KeyFrame2[playIndex2].inc_posTB3 = (KeyFrame2[playIndex2 + 1].posTB3 - KeyFrame2[playIndex2].posTB3) / i_max_steps2;
    KeyFrame2[playIndex2].inc_posTN1 = (KeyFrame2[playIndex2 + 1].posTN1 - KeyFrame2[playIndex2].posTN1) / i_max_steps2;
    KeyFrame2[playIndex2].inc_posTN2 = (KeyFrame2[playIndex2 + 1].posTN2 - KeyFrame2[playIndex2].posTN2) / i_max_steps2;
    KeyFrame2[playIndex2].inc_posTN3 = (KeyFrame2[playIndex2 + 1].posTN3 - KeyFrame2[playIndex2].posTN3) / i_max_steps2;
    
}



//TERMINA KEYFRAMES



int main( )
{
    
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "AnayaRuizYairAlejandro_Proyecto_Gpo09 ", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    //SKYBOX
    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };


    GLuint indicesSK[] =
    {  // Note that we start from 0!
        0,1,2,3,
        4,5,6,7,
        8,9,10,11,
        12,13,14,15,
        16,17,18,19,
        20,21,22,23,
        24,25,26,27,
        28,29,30,31,
        32,33,34,35
    };

    // Positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    //SkyBox
    GLuint skyboxVBO, skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Load textures
    vector<const GLchar*> faces;
    faces.push_back("SkyBox/right.tga");
    faces.push_back("SkyBox/left.tga");
    faces.push_back("SkyBox/top.tga");
    faces.push_back("SkyBox/bottom.tga");
    faces.push_back("SkyBox/back.tga");
    faces.push_back("SkyBox/front.tga");

    GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);
    //TERMINA SKY


    //*********PLANO*********
    float vertices[] =
    {
        // Positions                  // Normals              // Texture Coords
         -9.17f,  -3.5+2.73, -3.0-4.0f,    0.0f, 0.0f,-1.0f,		    0.0f,0.0f, //0
         -9.17f, -3.5 + 2.73, 3.0- 4.0f,	   0.0f, 0.0f,-1.0f,		1.0f,0.0f, //1
         -7.7f,  3.5+ 2.73, 3.0 - 4.0f,     0.0f, 0.0f,-1.0f,		1.0f,1.0f, //2
         -7.7f,  3.5 + 2.73, -3.0 - 4.0f,    0.0f, 0.0f,-1.0f,		0.0f,1.0f, //3
    };
    int indices[] = 
    {
        0,1,3,
        1,2,3,
    };
    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Texture Coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // Load textures
    GLuint texture1;
    glGenTextures(1, &texture1);

    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    // Diffuse map
    image = stbi_load("images/Puerta.png", &textureWidth, &textureHeight, &nrChannels, 0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);



    //*********TERMINA PLANO *********
   

    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

    // Load models
    Model Casa((char *)"Models/Proyecto/casa.obj");
    Model Cama((char*)"Models/Proyecto/camaa.obj");
    Model CajaDeRegalo((char*)"Models/Proyecto/CajaDeRegalo.obj");
    Model Tapa((char*)"Models/Proyecto/Tapa.obj");
    Model Lampara((char*)"Models/Proyecto/Lampara.obj");
    Model Flores((char*)"Models/Proyecto/Flores.obj");
    Model Almohada((char*)"Models/Proyecto/almohada.obj");
    Model Barril((char*)"Models/Proyecto/Barril.obj");
    Model Mano((char*)"Models/Proyecto/Mano.obj");
    Model Brazo((char*)"Models/Proyecto/Brazo.obj");
    Model Piano((char*)"Models/Proyecto/piano.obj");
    Model TB1((char*)"Models/Proyecto/TB1.obj");
    Model TB2((char*)"Models/Proyecto/TB2.obj");
    Model TB3((char*)"Models/Proyecto/TB3.obj");
    Model TN1((char*)"Models/Proyecto/TN1.obj");
    Model TN2((char*)"Models/Proyecto/TN2.obj");
    Model TN3((char*)"Models/Proyecto/TN3.obj");
    

    //Inicialización de KeyFrames

    //Regalo

    for (int i = 0; i < NumFrames; i++)
    {
        KeyFrame[i].posRX = 0;
        KeyFrame[i].posRZ = 0;
        KeyFrame[i].inc_posRX = 0;
        KeyFrame[i].inc_posRZ = 0;
      
    }

    //Piano

    for (int j = 0; j < NumFrames2; j++)
    {
        KeyFrame2[j].posTB1 = 0;
        KeyFrame2[j].posTB2 = 0;
        KeyFrame2[j].posTB3 = 0;
        KeyFrame2[j].posTN1 = 0;
        KeyFrame2[j].posTN2 = 0;
        KeyFrame2[j].posTN3 = 0;
        
        KeyFrame2[j].inc_posTB1 = 0;
        KeyFrame2[j].inc_posTB2 = 0;
        KeyFrame2[j].inc_posTB3 = 0;
        KeyFrame2[j].inc_posTN1 = 0;
        KeyFrame2[j].inc_posTN2 = 0;
        KeyFrame2[j].inc_posTN3 = 0;
        

    }

    saveFrame();
    saveFrame2();

    // Draw in wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    
    
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    // Game loop
    while( !glfwWindowShouldClose( window ) )
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime( );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Check and call events
        glfwPollEvents( );
        DoMovement( );
        animacion();
        animacion2();

        // Clear the colorbuffer
        glClearColor(0.450f, 0.368f, 0.427f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        shader.Use( );
        glm::mat4 model = glm::mat4(1);
        
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );

        if (ActivaMano)
        {
            MovimientoDeMano();
        }
        
        if (ActivaRegalo == true || ActivaRegalo == false)
        {
            AbrirRegalo();
        }

        if (ActivaAlmohada == true || ActivaAlmohada == false)
        {
            MoverAlmohada();
        }

   
        // Draw the loaded model


        //CASA
        model = glm::mat4(1);
        model = glm::translate( model, glm::vec3( 0.0f, 0.0, 0.0f ) ); // Translate it down a bit so it's at the center of the scene
        // model = glm::scale( model, glm::vec3( 0.02f, 0.02f, 0.02f ) );	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv( glGetUniformLocation( shader.Program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
        Casa.Draw(shader);

		//CAJA DE REGALO
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(regaloX, regaloZ, 0.0f)); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CajaDeRegalo.Draw(shader);
        //TAPA
        model = glm::translate(model, glm::vec3(0.0f, 0.726f, 0.65f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(grados), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Tapa.Draw(shader);
        
        
        //CAMA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.82f, 0.0, -7.0f)); // Translate it down a bit so it's at the center of the scene
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cama.Draw(shader);
        //ALMOHADA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.7, 2.41, avaAlmo)); 
        model = glm::rotate(model, glm::radians(rotAlmo), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Almohada.Draw(shader);
        
        //LAMPARA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.62f, 7.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Lampara.Draw(shader);

        //BARRIL
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 9.0f)); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Barril.Draw(shader);

        //BRAZO 1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 9.0f)); // Translate it down a bit so it's at the center of the scene
        //model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Brazo.Draw(shader);

        //MANO 1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.67f, 3.0f, 9.5f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(mano), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mano.Draw(shader);

        //BRAZO 2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 8.0f)); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Brazo.Draw(shader);

        //MANO 2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.67f, 3.0f, 8.5f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(mano), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mano.Draw(shader);

        //BRAZO 3
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.0f, -0.5f, 8.5f)); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Brazo.Draw(shader);

        //MANO 3
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.67f, 2.5f, 9.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(mano), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mano.Draw(shader);

        //FLORES
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 9.5f)); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Flores.Draw(shader);

        
        //PIANO
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 9.5f)); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Piano.Draw(shader);

        //DIBUJAR PLANO
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        //TB1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.604f, 2.6f, 9.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(rotTB1), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        TB1.Draw(shader);
        //TB2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.77f, 2.6f, 9.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(rotTB2), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        TB2.Draw(shader);
        //TB3
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.58f, 2.6f, 9.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(rotTB3), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        TB3.Draw(shader);
        //TN1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.24f, 2.67f, 9.05f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(rotTN1), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        TN1.Draw(shader);
        //TN2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.94f, 2.67f, 9.05f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(rotTN2), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        TN2.Draw(shader);
        //TN3
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.83f, 2.67f, 9.05f)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(rotTN3), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        TN3.Draw(shader);

        //Skybox

        // Draw skybox as last
        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
        SkyBoxshader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // Set depth function back to default
       
        
       
        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
    //ANIMACIÓN DE LA CAJA DE REGALO
    if (keys[GLFW_KEY_3])
    {
        ActivaRegalo = !ActivaRegalo;
        
    }
    //ANIMACIÓN DE LA MANO
    if (keys[GLFW_KEY_4])
    {  
        ActivaMano = !ActivaMano;
    }
    //ANIMACIÓN ALMOHADA
    if (keys[GLFW_KEY_5])
    {
        ActivaAlmohada = !ActivaAlmohada;
    }
    //Teclas piano
    if (keys[GLFW_KEY_1])
    {
        if (play_piano == false)
        {
            resetElements2();
            interpolation2();
            play_piano = true;
            playIndex2 = 0;
            i_curr_steps2 = 0;
        }
        else
        {
            play_piano = false;
        }
        
    }
    //Brinca regalo
    if (keys[GLFW_KEY_2])
    {
        if (play_regalo == false)
        {
            resetElements();
            interpolation();
            play_regalo = true;
            playIndex = 0;
            i_curr_steps = 0;
        }
        else
        {
            play_regalo = false;
        }

    }
}
//Regalo
void animacion()
{

    if (play_regalo) {

        if (i_curr_steps >= i_max_steps) //end of animation between frames?
        {
            playIndex++;
            if (playIndex > FrameIndex - 2)	//end of total animation?
            {

                playIndex = 0;
                play_regalo = false;

            }
            else //Next frame interpolations
            {
                i_curr_steps = 0; //Reset counter
                                  //Interpolation
                interpolation();
            }
        }
        else
        {
            //Draw animation

            regaloX += KeyFrame[playIndex].inc_posRX;
            regaloZ += KeyFrame[playIndex].inc_posRZ;

            i_curr_steps++;
        }

    }

}

//Piano
void animacion2()
{

    if (play_piano) {

        if (i_curr_steps2 >= i_max_steps2) //end of animation between frames?
        {
            playIndex2++;
            if (playIndex2 > FrameIndex2 - 2)	//end of total animation?
            {

                playIndex2 = 0;
                play_piano = false;

            }
            else //Next frame interpolations
            {
                i_curr_steps2 = 0; //Reset counter
                                  //Interpolation
                interpolation2();
            }
        }
        else
        {
            //Draw animation

            rotTB1 += KeyFrame2[playIndex2].inc_posTB1;
            rotTB2 += KeyFrame2[playIndex2].inc_posTB2;
            rotTB3 += KeyFrame2[playIndex2].inc_posTB3;
            rotTN1 += KeyFrame2[playIndex2].inc_posTN1;
            rotTN2 += KeyFrame2[playIndex2].inc_posTN2;
            rotTN3 += KeyFrame2[playIndex2].inc_posTN3;

            i_curr_steps2++;
        }

    }

}

void MoverAlmohada()
{
    if (ActivaAlmohada == true)
    {
        if (avaAlmo < -3.7)
        {
            avaAlmo += 0.01;
            
            if (rotAlmo < 360)
            {
                
                rotAlmo += 0.6;
            }
        }
    }
    else
        if (ActivaAlmohada == false)
        {
            if (avaAlmo > -9.30)
            {
                avaAlmo -= 0.01;

                if (rotAlmo > 0)
                {
                    rotAlmo -= 0.6;
                }
            }
        }
}

void AbrirRegalo()
{
    if (ActivaRegalo == true)
    {
        if(grados < 200)
        {
            
            grados += 0.8;
        }
        
    }
    else
        if (ActivaRegalo == false)
        {
            if(grados > 0)
            {
                grados -= 0.8;
            }
        }
}

void MovimientoDeMano()
{
    if (estadoMano == 0)
    {
        if (mano > -90)
        {
            //mano -= 1;
            mano -= 1; 
        }
        else
        {
            estadoMano = 1;
        }
        
    }else
        if (estadoMano == 1)
        {
            if (mano < 0)
            {
                mano += 1;
            }
            else
            {
                estadoMano = 0; 
            }
        }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

