#include <engine.h>
#include <stdlib.h>
#include <string.h>

typedef struct PlayerPieces {
    uint64_t* kings;
    uint64_t* queens;
    uint64_t* rooks;
    uint64_t* knights;
    uint64_t* bishops;
    uint64_t* pawns;
} PlayerPieces;

// Helper Definitions
static void _loadStandardStartingChessBoard(EngineState*);
static bool _isMoveLegal(EngineState*, ChessMove);

static ChessMoveResponse _getMoves(EngineState*, PlayerColor);
static ChessMoveResponse __getKingMoves(PlayerPieces);
static ChessMoveResponse __getQueenMoves(PlayerPieces);
static ChessMoveResponse __getRookMoves(PlayerPieces);
static ChessMoveResponse __getKnightMoves(PlayerPieces);
static ChessMoveResponse __getBishopMoves(PlayerPieces);
static ChessMoveResponse __getPawnMoves(PlayerPieces);

static bool __isMoveEqual(ChessMove, ChessMove);
static ChessMoveResponse __combineChessMoveResponses(ChessMoveResponse, ChessMoveResponse);
static PlayerPieces __getPlayerPieces(EngineState*, PlayerColor);

static bool ___isChessSquareEqual(ChessSquare a, ChessSquare b);

// Memory
void initializeEngineState(EngineState* state, const size_t maxMoves) {
    state->moves = malloc(sizeof(*state->moves) * maxMoves);
    state->maximumMoveCount = maxMoves;
    _loadStandardStartingChessBoard(state);
}

void destroyEngineState(EngineState* state) {
    free(state->moves);
}

void destroyChessMoveResponse(ChessMoveResponse response) {
    free(response.moves);
}

// Logic
ChessMoveResponse getMoves(EngineState* state) {
    return _getMoves(state, state->currentPlayer);
}

EngineResponse makeMove(EngineState* state, ChessMove move) {
    EngineResponse errorResponse =  {.success=false};

    if (!_isMoveLegal(state, move)) {
        return errorResponse;
    }


}

EngineResponse undoMove(EngineState* state) {
    
}

void getBoardState(EngineState* engineState, BoardState* boardState) {
    
}

// Helpers
static void _loadStandardStartingChessBoard(EngineState* state) {

}

ChessMoveResponse _getMoves(EngineState* state, PlayerColor player) {
    PlayerPieces playerPieces = __getPlayerPieces(state, player);
    
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

bool _isMoveLegal(EngineState* state, ChessMove requestedMove) {
    ChessMoveResponse availableMoves = _getMoves(state, state->currentPlayer);

    for (size_t i = 0; i < availableMoves.totalMoves; ++i) {
        ChessMove currentMove = availableMoves.moves[i];

        if (__isMoveEqual(requestedMove, currentMove)) {
            return true;
        }
    }
    
    return false;
}

static ChessMoveResponse __getKingMoves(PlayerPieces pieces) {

}

static ChessMoveResponse __getQueenMoves(PlayerPieces pieces) {

}

static ChessMoveResponse __getRookMoves(PlayerPieces pieces) {

}

static ChessMoveResponse __getKnightMoves(PlayerPieces pieces) {

}

static ChessMoveResponse __getBishopMoves(PlayerPieces pieces) {

}

static ChessMoveResponse __getPawnMoves(PlayerPieces pieces) {

}

static ChessMoveResponse __combineChessMoveResponses(ChessMoveResponse a, ChessMoveResponse b) {
    size_t totalMoves = a.totalMoves + b.totalMoves;

    ChessMove* moves = malloc(sizeof(*moves) * totalMoves);

    memcpy(moves, a.moves, sizeof(*moves) * totalMoves);

    return (ChessMoveResponse) {
        .moves=moves,
        .totalMoves=totalMoves,
    };
}

static PlayerPieces __getPlayerPieces(EngineState* state, PlayerColor playerColor) {
    PlayerPieces toReturn;

    switch (playerColor) {
        case WHITE:
            toReturn.kings =   &state->bitBoard.whiteKings;
            toReturn.queens =  &state->bitBoard.whiteQueens;
            toReturn.rooks =   &state->bitBoard.whiteRooks;
            toReturn.knights = &state->bitBoard.whiteKnights;
            toReturn.bishops = &state->bitBoard.whiteBishops;
            toReturn.pawns =   &state->bitBoard.whitePawns;

            break;

        case BLACK:
            toReturn.kings =   &state->bitBoard.blackKings;
            toReturn.queens =  &state->bitBoard.blackQueens;
            toReturn.rooks =   &state->bitBoard.blackRooks;
            toReturn.knights = &state->bitBoard.blackKnights;
            toReturn.bishops = &state->bitBoard.blackBishops;
            toReturn.pawns =   &state->bitBoard.blackPawns;

            break;
    }
    
    return toReturn;
}

static bool __isMoveEqual(ChessMove a, ChessMove b) {
    if (a.totalPiecesMoved != b.totalPiecesMoved) {
        return false;
    }

    for (size_t i = 0; i < a.totalPiecesMoved; ++i) {
        if (!___isChessSquareEqual(a.from[i], b.from[i])) {
            return false;
        }

        if (!___isChessSquareEqual(a.to[i], b.to[i])) {
            return false;
        }
    }

    return true;
}

static bool ___isChessSquareEqual(ChessSquare a, ChessSquare b) {
    return a.file == b.file && a.rank == b.rank;
}