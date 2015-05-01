#include "ofMain.h"
#include "ofApp.h"
#ifdef USE_PROGRAMMABLE_GL
// tig: using the programmable GL renderer is more fun, since we can use GLSL 150 =)
// define USE_PROGRAMMABLE_GL in ofApp.h to run this example in OpenGL 3.2 if your
// system provides it...
#include "ofGLProgrammableRenderer.h"
#else
#include "ofAppGlutWindow.h"

#endif
//========================================================================
int main( ){
#ifdef USE_PROGRAMMABLE_GL
    // we are using the programmable gl renderer.
    
    ofPtr<ofBaseRenderer> renderer(new ofGLProgrammableRenderer(false));
    ofSetCurrentRenderer(renderer, false);
    ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context
    

#else
    // we are not using the progammable gl renderer.
    
    // when we are not using the programmable gl renderer it is not safe to assume
    // out current gl context provides us with the necessary openGL extensions to
    // run this example.
    
    // let's check if the current openGL context provides us with glDrawElementsInstanced
    // we do this after we have initialised our openGL context.
    ofAppGlutWindow window;
    window.setGlutDisplayString("rgba double samples>=8");
    ofSetupOpenGL(&window,1280,720,OF_WINDOW);			// <-------- setup the GL context
    ofSetLogLevel(OF_LOG_VERBOSE);
    ostringstream extStr;
    extStr << (char*)glGetString(GL_EXTENSIONS);		// first get all available extensions.
    string extensionsAvailable = extStr.str();
    
    
    if (ofStringTimesInString(extensionsAvailable, "GL_ARB_draw_instanced") == 0)
    {
        ofLogFatalError("App") << " GL_ARB_draw_instanced is needed for this example but it is not supported by your graphics card. Exiting App.";
        return -1;
        
    } else {
        
        // GL_ARB_draw_instanced is available... so far so good.
        
        // either one of these is needed, too:
        if (ofStringTimesInString(extensionsAvailable, "GL_EXT_gpu_shader4") == 0 &&
            ofStringTimesInString(extensionsAvailable, "NV_vertex_program4") == 0 )
        {
            ofLogFatalError("App") << " GL_EXT_gpu_shader4 or NV_vertex_program4 is needed for this example but it is not supported by your graphics card. Exiting App.";
            return -1;
            
        }
        
    }


#endif
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    
    ofRunApp( new ofApp());
}
