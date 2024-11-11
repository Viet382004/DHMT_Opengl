#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <vector_matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	 { 0.5f,	 0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	 { -0.5f,	 0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	 { -0.5f,	-0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	// v2-v3-v0
	 { -0.5f,	-0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	 { 0.5f,	-0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	 { 0.5f,	 0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },

	// v0-v3-v4 (right)
	 { 0.5f,	 0.5f,	 0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	 { 0.5f,	-0.5f,   0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	 { 0.5f,	-0.5f,  -0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	// v4-v5-v0
	 { 0.5f,	-0.5f,	-0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	 { 0.5f,	 0.5f,	-0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	 { 0.5f,	 0.5f,   0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },

	// v0-v5-v6 (top)
	 { 0.5f,	 0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { 0.5f,	0.5f,	-0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { -0.5f,	0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	 { -0.5f,	 0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { -0.5f,	0.5f,	0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { 0.5f,	0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v1-v6-v7 (left)
	 { -0.5f,	 0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { -0.5f,	0.5f,	-0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { -0.5f,	-0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	 { -0.5f,	 -0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { -0.5f,	-0.5f,	0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
	 { -0.5f,	0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	 { -0.5f,	 -0.5f,	 -0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
	 { 0.5f,	-0.5f,	-0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
	 { 0.5f,	-0.5f,	 0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	 { 0.5f,	 -0.5f,	 0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
	 { -0.5f,	-0.5f,	0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
	 { -0.5f,	-0.5f,	 -0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ 0.5f,	 -0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ -0.5f,	-0.5f,	-0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ -0.5f,	0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ -0.5f,	 0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ 0.5f,	0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ 0.5f,	-0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int 
	CurrentWidth = 700,
	CurrentHeight = 700;

mat4 model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int model_mat_location,
view_mat_location,
projection_mat_location;

float Alpha = 0.0f;
float t[] = { 0.0f, 0.0f, 0.0f };


bool translated = false;

GLuint
	VaoId,
	VboId,
	VertexShaderId,
	FragmentShaderId,
	ProgramId;

// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

// ---------------------------------------------------------------------------	
void day()
{
	mat4 instance = identity_mat4();
	instance =  scale(vec3(1.0, 1.0, 0.1));
	mat4 model_day = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_day.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhtrai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.45, 0.0, -0.25)) * scale(vec3(0.1, 1.0, 0.4));
	mat4 model_canhtrai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_canhtrai.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhphai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.45, 0.0, -0.25)) * scale(vec3(0.1, 1.0, 0.4));
	mat4 model_canhphai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_canhphai.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhtren()
{
	mat4 instance = identity_mat4();
	instance = rotate_z(-90) * translate(vec3(-0.45, 0.0, -0.25)) * scale(vec3(0.1, 1.0, 0.4));
	mat4 model_canhtrai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_canhtrai.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhduoi()
{
	mat4 instance = identity_mat4();
	instance = rotate_z(-90) * translate(vec3(0.45, 0.0, -0.25)) * scale(vec3(0.1, 1.0, 0.4));
	mat4 model_canhphai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_canhphai.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void num()
{
	mat4 instance = identity_mat4();
	instance =  translate(vec3(0.0, -0.55, -0.25)) * scale(vec3(0.4, 0.1, 0.1));
	mat4 model_canhphai =  model_mat_cpp * instance ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_canhphai.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void nganban()
{
	day();
	canhtrai();
	canhphai();
	canhtren();
	canhduoi();
}

// ---------------------------------------------------------------------------

void DisplayFunc(void)
{
	vec3 eye(3.0f, 5.0f, -2.0f),  // Di chuyển camera sang phải
		at(0.0f, 0.0f, 0.0f),    // Camera nhìn về điểm gốc
		up(0.0f, 1.0f, 0.0f);
		
	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	// Các tham số của phép chiếu perspective
	float
		znear = 1.0f,
		zfar = 100.0f,
		fov = 67.0f,
		aspect = (float)CurrentWidth / CurrentHeight;

	// Tạo ma trận projection 
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CW);	

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);

	model_mat_cpp = model_mat_cpp * rotate_x(90);

	
	model_mat_cpp =  model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	
	nganban();
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, -0.55, -0.25)) * rotate_y(Alpha) * translate(vec3(0.0, 0.55, 0.25));

	num();

	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;
	case 't':
		t[1] -= 0.1f; 
		translated = true;
		break;
	case 's':
		t[1] += 0.1f;
		translated = true;
		break;
	case 'q':
		Alpha += 5.0f;
		break;
	case 'Q':
		Alpha -= 5.0f;
		break;
	}
}
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);	
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Cube");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);	
	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}
// --------------------------------------
bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}