#include <engine.h>
#include <stdlib.h>
#include <string.h>

typedef struct PlayerPieces {
    uint64_t* kings;
    uint64_t* queens;
    uint64_t* rooks;
    uint64_t* knights;
    uint64_t* bishops;
    uint64_t* pawn;
} PlayerPieces;

// Helper Definitions
static void _loadStandardStartingChessBoard(EngineState*);

static ChessMoveResponse _getKingMoves(PlayerPieces);
static ChessMoveResponse _getQueenMoves(PlayerPieces);
static ChessMoveResponse _getRookMoves(PlayerPieces);
static ChessMoveResponse _getKnightMoves(PlayerPieces);
static ChessMoveResponse _getBishopMoves(PlayerPieces);
static ChessMoveResponse _getPawnMoves(PlayerPieces);

static ChessMoveResponse __combineChessMoveResponses(ChessMoveResponse, ChessMoveResponse);
static PlayerPieces __getPlayerPieces(EngineState*, PlayerColor);

// Memory
void initializeEngineState(EngineState* state, const size_t maxMoves) {
    state->moves = malloc(sizeof(*state->moves) * maxMoves);
    state->maximumMoveCount = maxMoves;
}

void destroyEngineState(EngineState* state) {
    free(state->moves);
}

void destroyChessMoveResponse(ChessMoveResponse response) {
    free(response.moves);
}

// Logic
ChessMoveResponse getMoves(EngineState* state) {
    PlayerPieces playerPieces = __getPlayerPieces(state, state->currentPlayer);

    ChessMoveResponse kingMoves = _getKingMoves(playerPieces);
    ChessMoveResponse queenMoves = _getQueenMoves(playerPieces);
    ChessMoveResponse rookMoves = _getRookMoves(playerPieces);
    ChessMoveResponse knightMoves = _getKnightMoves(playerPieces);
    ChessMoveResponse bishopMoves = _getBishopMoves(playerPieces);
    ChessMoveResponse pawnMoves = _getPawnMoves(playerPieces);

    ChessMoveResponse groupA = __combineChessMoveResponses(kingMoves, queenMoves);
    ChessMoveResponse groupB = __combineChessMoveResponses(rookMoves, knightMoves);
    ChessMoveResponse groupC = __combineChessMoveResponses(bishopMoves, pawnMoves);

    ChessMoveResponse groupD = __combineChessMoveResponses(groupA, groupB);
    
    return __combineChessMoveResponses(groupC, groupD);
}

bool makeMove(EngineState*, ChessMove) {

}

bool undoMove(EngineState*) {

}

BoardState getBoardState(EngineState*) {

}

// Helpers
static ChessMoveResponse _getKingMoves(PlayerPieces) {

}

static ChessMoveResponse _getQueenMoves(PlayerPieces) {

}

static ChessMoveResponse _getRookMoves(PlayerPieces) {

}

static ChessMoveResponse _getKnightMoves(PlayerPieces) {

}

static ChessMoveResponse _getBishopMoves(PlayerPieces) {

}

static ChessMoveResponse _getPawnMoves(PlayerPieces) {

}

static ChessMoveResponse __combineChessMoveResponses(ChessMoveResponse a, ChessMoveResponse b) {
    size_t totalMoves = a.totalMoves + b.totalMoves;

    ChessMove* moves = malloc(sizeof(*moves) * totalMoves);

    memcpy(moves, a.moves, sizeof());

    return (ChessMoveResponse) {
        .moves=moves,
        .totalMoves=totalMoves,
    };
}

static PlayerPieces __getPlayerPieces(EngineState*, PlayerColor) {

}