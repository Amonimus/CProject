#include "utils/Logger/Logger.cpp"
#include "App/App.cpp"
#include "Base/Color/Color.cpp"

// Create window
void start_app(){
    Color bg_color = Color(1, 0, 1);
    App app = App(L"DirectX app", 640, 480, L"res/computer.ico", &bg_color);
    app.run();
}

// MAIN
int main(int argc, char const *argv[]){
    logger.debug("Hello", "world!");
    start_app();
    return 0;
}
