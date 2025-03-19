#include <iostream>
#include <conio.h>  // Para _kbhit() y _getch()
#include <windows.h>  // Para la detección del clic del ratón
#include <string>

// Definir los estados
enum class CharacterState {
    Standing,
    Jumping,
    Diving,
    Ducking,
    Crouching,
    WalkingLeft,
    WalkingRight
};

class Character {
private:
    CharacterState currentState;
    CharacterState previousState;

public:
    Character() : currentState(CharacterState::Standing), previousState(CharacterState::Standing) {}

    // Cambiar el estado del personaje
    void changeState(CharacterState newState) {
        if (currentState != newState) { // Solo cambia si el estado es diferente
            previousState = currentState;
            currentState = newState;
            std::cout << "Estado cambiado a: " << getStateName() << std::endl;
        }
    }

    // Realizar una acción según el estado actual
    void performAction() {
        switch (currentState) {
        case CharacterState::Standing:
            // No se necesita mensaje si ya está de pie y no ha cambiado
            break;
        case CharacterState::Jumping:
            // No se necesita mensaje si ya está saltando y no ha cambiado
            break;
        case CharacterState::Diving:
            // No se necesita mensaje si ya está buceando y no ha cambiado
            break;
        case CharacterState::Ducking:
            // No se necesita mensaje si ya está agachado (ducking) y no ha cambiado
            break;
        case CharacterState::Crouching:
            // No se necesita mensaje si ya está agachado (crouching) y no ha cambiado
            break;
        case CharacterState::WalkingLeft:
            // No se necesita mensaje si ya está caminando a la izquierda y no ha cambiado
            break;
        case CharacterState::WalkingRight:
            // No se necesita mensaje si ya está caminando a la derecha y no ha cambiado
            break;
        }
    }

    // Obtener el nombre del estado actual (para mostrar en consola)
    std::string getStateName() const {
        switch (currentState) {
        case CharacterState::Standing: return "De pie";
        case CharacterState::Jumping: return "Saltando";
        case CharacterState::Diving: return "Buceando";
        case CharacterState::Ducking: return "CUACK";
        case CharacterState::Crouching: return "Agachado (crouch)";
        case CharacterState::WalkingLeft: return "Caminando hacia la izquierda";
        case CharacterState::WalkingRight: return "Caminando hacia la derecha";
        default: return "Desconocido";
        }
    }

    // Detectar entradas del teclado y ratón
    void handleInput() {
        if (_kbhit()) {
            char key = _getch(); // Lee una tecla presionada

            switch (key) {
            case 'w': // Salta
                changeState(CharacterState::Jumping);
                break;
            case 'a': // Camina a la izquierda
                changeState(CharacterState::WalkingLeft);
                break;
            case 'd': // Camina a la derecha
                changeState(CharacterState::WalkingRight);
                break;
            case 's': // Crouch (agachado)
                changeState(CharacterState::Crouching);
                break;
            case ' ': // Salta
                changeState(CharacterState::Jumping);
                break;
            default:
                changeState(CharacterState::Standing); // Si no se presiona nada relevante, sigue de pie
            }
        }

        // Verifica si se hizo clic con el ratón izquierdo (botón 0)
        if (GetAsyncKeyState(VK_LBUTTON)) { // VK_LBUTTON es el código para el clic izquierdo
            changeState(CharacterState::Ducking);
        }
    }
};

int main() {
    Character character;

    while (true) {
        character.handleInput();
        character.performAction();
        Sleep(50);  // Pausa breve para evitar usar demasiados recursos de la CPU
    }

    return 0;
}
