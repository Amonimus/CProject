#include "DirectX/Window/AppWindow.cpp"

void start_app(){
    AppWindow app(L"Window Name", 1024, 768, L"res/computer.ico");
    app.run();
}

int main(int argc, char const *argv[]){
    // Main
    start_app();
    return 0;
}
