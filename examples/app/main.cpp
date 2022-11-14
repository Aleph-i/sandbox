#include <iostream>

#include "sandbox/plugin/plugin_manager.h"
#include "sandbox/plugin/plugin_interface.h"
#include "sandbox/interfaces/entity_component_interface.h"
#include "sandbox/entity.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    std::cout << "This is a test." << std::endl;

    using namespace sandbox;

    PluginManager pm;
    EntityComponentInterface* ec = new EntityComponentInterface();
    pm.addPluginInterface(ec);
    pm.loadPlugin("lib/libtest.so");
    pm.loadPlugin("lib/libglfw_sandbox.so");
    pm.loadPlugin("lib/libopengl_sandbox.so");

    Entity root("Root");
    Entity& display = root.addChild(new Entity("Display"));
    display.addComponent(ec->components().create("GLFWWindow"));
    Component& window = display.addComponent(ec->components().create("GLFWWindow"));
    window["width"].set<int>(700);
    window["title"].set<std::string>("Something else");
    display.addComponent(ec->components().create("OpenGLTest"));

    Task& print = *ec->tasks().create("PrintTask");
    root.runTask(print);

    Task& initContext = *ec->tasks().create("GLFWInitContext");
    root.runTask(initContext);
    Task& swapBuffers = *ec->tasks().create("GLFWSwapBuffers");
    Task& pollEvents = *ec->tasks().create("GLFWPollEvents");
    Task& makeCurrent = *ec->tasks().create("GLFWMakeCurrent");
    Task& init = *ec->tasks().create("OpenGLInit");
    Task& run = *ec->tasks().create("OpenGLRun");

        root.runTask(makeCurrent);
        root.runTask(init);
        root.runTask(run);
        root.runTask(swapBuffers);
        root.runTask(pollEvents);

    while (true) {
        //usleep(100000);

        root.runTask(makeCurrent);
        root.runTask(run);
        root.runTask(swapBuffers);
        root.runTask(pollEvents);

        std::cout << window["width"].get<int>() << std::endl;
        //std::cout << "step" << std::endl;
    }

    return 0;
}