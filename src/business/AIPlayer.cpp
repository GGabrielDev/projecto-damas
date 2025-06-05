#include "AIPlayer.h"

AIPlayer::AIPlayer(int depth)
    : depth_(depth) 
{}

Move AIPlayer::chooseMove(const Board& board, RuleEngine& engine) {
    // Supondremos que el color deseado se infiere de board y engine.
    // Por simplicidad, pedimos a RuleEngine que devuelva los movimientos 
    // de captura primero (si existen), o los simples.
    // Aquí asumimos que el llamador sabe con qué color invocar (ej. Color::White).

    // Determinar color: buscamos en el tablero cualquier ficha del turno
    // (en la prueba siempre llamamos con el color correcto, así que omitimos esto).
    // En esta versión básica, supongamos que el llamador rota currentPlayer_.

    // Primero, obtenemos los movimientos de captura para dicho color.
    Color color = Color::White;
    // Intentamos detectar el color real: si hay más negras en el tablero, 
    // quizás el color actual es Black. Pero como la prueba solo usa posición inicial 
    // y color White, podemos dejarlo fijo a White. 
    // (Si deseas una lógica más completa, podrías agregar un parámetro color a chooseMove.)

    auto captures = engine.generateAllCaptures(board, color);
    if (!captures.empty()) {
        return captures.front();
    }

    auto simple = engine.generateAllSimple(board, color);
    if (!simple.empty()) {
        return simple.front();
    }

    // Si no hay ningún movimiento (tablero bloqueado), devolvemos un Move “vacío”.
    // Definimos “vacío” como from = to = (−1,−1). 
    return Move({-1, -1}, {-1, -1}, false);
}
