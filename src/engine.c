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
static bool _isMoveEqual(ChessMove, ChessMove);
static ChessMoveResponse _getMoves(EngineState*, PlayerColor);

static ChessMoveResponse __getKingMoves(PlayerPieces);
static ChessMoveResponse __getQueenMoves(PlayerPieces);
static ChessMoveResponse __getRookMoves(PlayerPieces);
static ChessMoveResponse __getKnightMoves(PlayerPieces);
static ChessMoveResponse __getBishopMoves(PlayerPieces);
static ChessMoveResponse __getPawnMoves(PlayerPieces);

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

    ChessMoveResponse kingMoves =   __getKingMoves(playerPieces);
    ChessMoveResponse queenMoves =  __getQueenMoves(playerPieces);
    ChessMoveResponse rookMoves =   __getRookMoves(playerPieces);
    ChessMoveResponse knightMoves = __getKnightMoves(playerPieces);
    ChessMoveResponse bishopMoves = __getBishopMoves(playerPieces);
    ChessMoveResponse pawnMoves =   __getPawnMoves(playerPieces);

    ChessMoveResponse groupA = __combineChessMoveResponses(kingMoves, queenMoves);
    ChessMoveResponse groupB = __combineChessMoveResponses(rookMoves, knightMoves);
    ChessMoveResponse groupC = __combineChessMoveResponses(bishopMoves, pawnMoves);

    ChessMoveResponse groupD = __combineChessMoveResponses(groupA, groupB);
    
    return __combineChessMoveResponses(groupC, groupD);
}

bool makeMove(EngineState* state, ChessMove move) {
    ChessMoveResponse availableMoves = 
}

bool undoMove(EngineState*) {

}

BoardState getBoardState(EngineState*) {

}

// Helpers
static ChessMoveResponse __getKingMoves(PlayerPieces) {

}

static ChessMoveResponse __getQueenMoves(PlayerPieces) {

}

static ChessMoveResponse __getRookMoves(PlayerPieces) {

}

static ChessMoveResponse __getKnightMoves(PlayerPieces) {

}

static ChessMoveResponse __getBishopMoves(PlayerPieces) {

}

static ChessMoveResponse __getPawnMoves(PlayerPieces) {

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