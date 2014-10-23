/*
 * The MIT License
 *
 * Copyright (c) 2010 Paul Solt, PaulSolt@gmail.com 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "GlutFramework.h"

namespace glutFramework {

	// Set constants
	const double GlutFramework::FRAME_TIME = 1.0 / GlutFramework::FPS * 1000.0; // Milliseconds

	
	GlutFramework *GlutFramework::instance = NULL;
	
	GlutFramework::GlutFramework() { 
		elapsedTimeInSeconds = 0;
		frameTimeElapsed = 0;
		title = "Procedural City";
		eyeVector = glm::vec3(0.0, 0.0, -10.0); // move the eye position back
		position = 0.0f;
		direction = 1.0 / FRAME_TIME;
		//	menu
		mainMenu = 0;
		menuFlag = 0;

	}
	
	GlutFramework::~GlutFramework() {
	}
	
	void GlutFramework::startFramework(int argc, char *argv[]) {

		if (argc < 2 || argc > 3) {
			//Usage instructions for core and challenge
			printf("Input value should be integers\n");
			printf("./city WIDTH LENGTH\n");
			printf("Using predetermined values to create the city (500,500)\n");
			citySize = glm::vec2 (500, 500);
		}
		else
		{
			citySize = glm::vec2 (atoi(argv[1]), atoi(argv[2]));
		}

		setInstance();	// Sets the instance to self, used in the callback wrapper functions
		
		// Initialize GLUT
		glutInit(&argc, argv);
//		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutCreateWindow(title.c_str()); 
		
		// Function callbacks with wrapper functions
		glutReshapeFunc(reshapeWrapper);
		glutMouseFunc(mouseButtonPressWrapper);
		glutMotionFunc(mouseMoveWrapper);
		glutPassiveMotionFunc(mouseMovePassiveWrapper);
		glutDisplayFunc(displayWrapper);
		glutKeyboardFunc(keyboardDownWrapper);
		glutKeyboardUpFunc(keyboardUpWrapper);
		glutSpecialFunc(specialKeyboardDownWrapper);
		glutSpecialUpFunc(specialKeyboardUpWrapper);
		
		init();						// Initialize
		createPopupMenus();			// Create menu
		glutIdleFunc(runWrapper); 	// The program run loop
		glutMainLoop();				// Start the main GLUT thread
	}
	
	void GlutFramework::load() {
		// Subclass and override this method
	}
	
	void GlutFramework::display(float dTime) {
		// Subclass and override this method
	}

	void GlutFramework::reshape(int width, int height) {
		glViewport(0,0,(GLsizei)width,(GLsizei)height);
	}

	void GlutFramework::mouseButtonPress(int button, int state, int x, int y) {
		printf("MouseButtonPress: x: %d y: %d\n", x, y);

	}

	void GlutFramework::mouseMove(int x, int y) {
//		printf("MouseMove: x: %d y: %d\n", x, y);
	}

	void GlutFramework::mouseMovePassive(int x, int y) {
//			printf("MouseMove: x: %d y: %d\n", x, y);
	}

	void GlutFramework::keyboardDown( unsigned char key, int x, int y )
	{
		// Subclass and override this method
		printf( "KeyboardDown: %c = %d\n", key, (int)key );
		if (key==27) { //27 =- ESC key
			exit (0);
		}

		keyStates.keyDown( (int)key );
	}

	void GlutFramework::keyboardUp( unsigned char key, int x, int y )
	{
		// Subclass and override this method
		printf( "KeyboardUp: %c \n", key );
		keyStates.keyUp( (int)key );
	}

	void GlutFramework::specialKeyboardDown( int key, int x, int y )
	{
		// Subclass and override this method
		printf( "SpecialKeyboardDown: %d\n", key );
	}

	void GlutFramework::specialKeyboardUp( int key, int x, int y )
	{
		// Subclass and override this method
		printf( "SpecialKeyboardUp: %d \n", key );
	}

	void GlutFramework::createPopupMenus()
	{
		mainMenu = glutCreateMenu(processMainMenuWrapper);
		//subclass method
		this->createMenuItens();
		// this will allow us to know if the menu is active
		glutMenuStatusFunc(processMenuStatusWrapper);
	}
	void GlutFramework::processMenuStatus(int status, int x, int y)
	{
		// Subclass and override this method
	}
	void GlutFramework::processMainMenu(int option)
	{
		// Subclass and override this method
	}

	void GlutFramework::createMenuItens()
	{
		// Subclass and override this method
	}
	// ******************************
	// ** Graphics helper routines **
	// ******************************
	
	// Initialize the projection/view matricies.
	void GlutFramework::setDisplayMatricies() {
		/* Setup the projection and model view matricies */
		int width = glutGet( GLUT_WINDOW_WIDTH );
		int height = glutGet( GLUT_WINDOW_HEIGHT );
		float aspectRatio = width/height;
		glViewport( 0, 0, width, height );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		//gluPerspective( 20, aspectRatio, 1, 1000.0 );
		gluPerspective(G308_FOVY, (double) width / (double) height, G308_ZNEAR_3D, G308_ZFAR_3D);


		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
				  centerVector.x, centerVector.y, centerVector.z,
				  upVector.x, upVector.y, upVector.z);
	}
	
	void GlutFramework::setupLights() {
//		GLfloat light1_position[] = { 0.0, 200.0, 200.0, 0.0 };
//		GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
//		GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
//		GLfloat ambient_light[] = { 0.8, 0.8, 0.8, 1.0 };
//
//		glLightfv( GL_LIGHT0, GL_POSITION, light1_position );
//		glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light );
//		glLightfv( GL_LIGHT0, GL_DIFFUSE, white_light );
//		glLightfv( GL_LIGHT0, GL_SPECULAR, white_light );
//
//		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel_ambient );

		float direction[] = { 1.0f, 1.0f, 1.0f, 0.0f };
		float diffintensity[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, direction);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffintensity);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		glEnable(GL_LIGHT0);

	}
	
	void GlutFramework::setShaders()
	{
		// Subclass and override this method
	}


	GLuint GlutFramework::createProgram(const char ffile[],const char vfile[])
	{

		GLuint program;
		GLuint v,f;
		char *vs = NULL,*fs = NULL;

		v = glCreateShader(GL_VERTEX_SHADER);
		f = glCreateShader(GL_FRAGMENT_SHADER);

		vs = textFileRead(vfile);
		fs = textFileRead(ffile);

		const char * ff = fs;
		const char * vf = vs;

		glShaderSource(v, 1, &vf,NULL);
		glShaderSource(f, 1, &ff,NULL);

		glCompileShader(v);
		glCompileShader(f);

		GLint status;
		glGetShaderiv(v, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			int loglen;
			char logbuffer[1000];
			glGetShaderInfoLog(v, sizeof(logbuffer), &loglen, logbuffer);
			fprintf(stderr, "Vertice Shader Compile Error:%d:\n%s", loglen, logbuffer);
		}

		glGetShaderiv(f, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			int loglen;
			char logbuffer[1000];
			glGetShaderInfoLog(f, sizeof(logbuffer), &loglen, logbuffer);
			fprintf(stderr, "Fragment Shader Compile Error:%d:\n%s", loglen, logbuffer);
		}

		program = glCreateProgram();
		glAttachShader(program,f);
		glAttachShader(program,v);

		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			int loglen;
			char logbuffer[1000];
			glGetProgramInfoLog(program, sizeof(logbuffer), &loglen, logbuffer);
			fprintf(stderr, "OpenGL Program Linker Error:\n%.*s", logbuffer);
		}
		free(vs);
		free(fs);
		return program;

	}

	void GlutFramework::setLookAt(float eyeX, float eyeY, float eyeZ, 
								  float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
		
		eyeVector = glm::vec3(eyeX, eyeY, eyeZ);
		centerVector = glm::vec3(centerX, centerY, centerZ);
		upVector = glm::vec3(upX, upY, upZ);
	}
	
	glm::vec3 GlutFramework::getEyeVector() const {
		return eyeVector;
	}
	
	glm::vec3 GlutFramework::getCenterVector() const {
		return centerVector;
	}
	
	glm::vec3 GlutFramework::getUpVector() const {
		return upVector;
	}
	
	void GlutFramework::setTitle(std::string theTitle) {
		title = theTitle;
	}
	
	// **************************
	// ** GLUT Setup functions **
	// **************************
	void GlutFramework::init() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		
		load();
	}
	
	void GlutFramework::setInstance() {
		//std::cout << "GlutFramework::setInstance()" << std::endl;
		instance = this;
	}
	
	void GlutFramework::run() {
		if(frameRateTimer.isStopped()) {	// The initial frame has the timer stopped, start it once
			frameRateTimer.start();
		}	
		
		frameRateTimer.stop();			// stop the timer and calculate time since last frame
		double milliseconds = frameRateTimer.getElapsedMilliseconds();
		frameTimeElapsed += milliseconds;
		
		if( frameTimeElapsed >= FRAME_TIME ) {	// If the time exceeds a certain "frame rate" then show the next frame
			glutPostRedisplay();
			frameTimeElapsed -= FRAME_TIME;		// remove a "frame" and start counting up again
		}
		frameRateTimer.start();			// start the timer
	}
	
	void GlutFramework::displayFramework() {
		if(displayTimer.isStopped()) {			// Start the timer on the initial frame
			displayTimer.start();
		}
		
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear once
		
		displayTimer.stop();		// Stop the timer and get the elapsed time in seconds
		elapsedTimeInSeconds = displayTimer.getElapsedSeconds(); // seconds
		
		//setupLights();

		//inside of setcamera
		//setDisplayMatricies();
		
		display(elapsedTimeInSeconds);
		
		glutSwapBuffers();
		displayTimer.start();		// reset the timer to calculate the time for the next frame
	}
	
	// ******************************************************************
	// ** Static functions which are passed to Glut function callbacks **
	// ******************************************************************
	
	void GlutFramework::displayWrapper() {
		instance->displayFramework(); 
	}
	
	void GlutFramework::reshapeWrapper(int width, int height) {
		instance->reshape(width, height);
	}
	
	void GlutFramework::runWrapper() {
		instance->run();
	}
	
	void GlutFramework::mouseButtonPressWrapper(int button, int state, int x, int y) {
		instance->mouseButtonPress(button, state, x, y);
	}
	
	void GlutFramework::mouseMoveWrapper(int x, int y) {
		instance->mouseMove(x, y);
	}

	void GlutFramework::mouseMovePassiveWrapper(int x, int y) {
			instance->mouseMovePassive(x, y);
	}
										 
	void GlutFramework::keyboardDownWrapper(unsigned char key, int x, int y) {
		instance->keyboardDown(key,x,y);
	}
	
	void GlutFramework::keyboardUpWrapper(unsigned char key, int x, int y) {
		instance->keyboardUp(key,x,y);
	}
	
	void GlutFramework::specialKeyboardDownWrapper(int key, int x, int y) {
		instance->specialKeyboardDown(key,x,y);
	}
	
	void GlutFramework::specialKeyboardUpWrapper(int key, int x, int y) {
		instance->specialKeyboardUp(key,x,y);
	}
	
	void GlutFramework::processMainMenuWrapper(int option){
		instance->processMainMenu(option);
	}

	void GlutFramework::processMenuStatusWrapper(int status, int x, int y){
		instance->processMenuStatus(status, x, y);
	}

} // namespace
