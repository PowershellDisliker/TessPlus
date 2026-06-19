#include <engine.h>
#include <stdlib.h>
#include <string.h>

#define WHITE_STARTING_KINGS 0
#define WHITE_STARTING_QUEENS 0
#define WHITE_STARTING_ROOKS 0
#define WHITE_STARTING_KNIGHTS 0
#define WHITE_STARTING_BISHOPS 0
#define WHITE_STARTING_PAWNS 0
#define BLACK_STARTING_KINGS 0
#define BLACK_STARTING_QUEENS 0
#define BLACK_STARTING_ROOKS 0
#define BLACK_STARTING_KNIGHTS 0
#define BLACK_STARTING_BISHOPS 0
#define BLACK_STARTING_PAWNS 0

// Helper Definitions / Declarations
typedef struct PlayerPieces {
    uint64_t* kings;
    uint64_t* queens;
    uint64_t* rooks;
    uint64_t* knights;
    uint64_t* bishops;
    uint64_t* pawns;
} PlayerPieces;

static void _loadStandardStartingChessBoard(EngineState*);
static bool _isMoveLegal(EngineState*, ChessMove);
static bool _movePiece(EngineState*, ChessPiece, ChessSquare, ChessSquare);

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

static bool ___isChessSquareEqual(ChessSquare, ChessSquare);
static bool ___isChessPieceEqual(ChessPiece, ChessPiece);

// Memory
void initializeEngineState(EngineState* state, const size_t maxMoves) {
    _loadStandardStartingChessBoard(state);

    state->moves = malloc(sizeof(*state->moves) * maxMoves);
    state->maximumMoveCount = maxMoves;
    state->currentPlayer = WHITE;
    state->flags.whiteCanCastleKingSide = true;
    state->flags.whiteCanCastleQueenSide = true;
    state->flags.blackCanCastleKingSide = true;
    state->flags.blackCanCastleQueenSide = true;

    // Get white's available moves
    state->availableMoves.moves = NULL;
    state->availableMoves.totalMoves = 0;
}

void freeEngineState(EngineState* state) {
    free(state->moves);
}

void freeChessMoveResponse(ChessMoveResponse response) {
    free(response.moves);
}

// Logic
ChessMoveResponse getMoves(EngineState* state) {
    return state->availableMoves;
}

EngineResponse makeMove(EngineState* state, ChessMove move) {
    EngineResponse errorResponse = {.success=false};

    if (state->moveCount >= state->maximumMoveCount) {
        return errorResponse;
    }
    
    if (!_isMoveLegal(state, move)) {
        return errorResponse;
    }

    _movePiece(state, move.movedPieceType, move.from, move.to);

    if (move.isCastling) {
        _movePiece(state, move.castlingPieceType, move.castlingRookFrom, move.castlingRookTo);
    }

    state->moves[state->moveCount] = move;
    state->moveCount++;

    return (EngineResponse) {
        .success = true,
    };
}

EngineResponse undoMove(EngineState* state) {
    
}

void getBoardState(EngineState* engineState, BoardState* boardState) {
    
}

// Helper Definitions
static void _loadStandardStartingChessBoard(EngineState* state) {
    BitBoards* bitBoards = &state->bitBoard;

    bitBoards->whiteKings = WHITE_STARTING_KINGS;
    bitBoards->whiteQueens = WHITE_STARTING_QUEENS;
    bitBoards->whiteRooks = WHITE_STARTING_ROOKS;
    bitBoards->whiteKnights = WHITE_STARTING_KNIGHTS;
    bitBoards->whiteBishops = WHITE_STARTING_BISHOPS;
    bitBoards->whitePawns = WHITE_STARTING_PAWNS;

    bitBoards->blackKings = BLACK_STARTING_KINGS;
    bitBoards->blackQueens = BLACK_STARTING_QUEENS;
    bitBoards->blackRooks = BLACK_STARTING_ROOKS;
    bitBoards->blackKnights = BLACK_STARTING_KNIGHTS;
    bitBoards->blackBishops = BLACK_STARTING_BISHOPS;
    bitBoards->blackPawns = BLACK_STARTING_PAWNS;
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

static bool _movePiece(EngineState* state, ChessPiece piece, ChessSquare from, ChessSquare to) {
    
}

ChessMoveResponse _getMoves(EngineState* state, PlayerColor player) {
    PlayerPieces playerPieces = __getPlayerPieces(state, player);
    
    ChessMoveResponse kingMoves   = __getKingMoves(playerPieces);
    ChessMoveResponse queenMoves  = __getQueenMoves(playerPieces);
    ChessMoveResponse rookMoves   = __getRookMoves(playerPieces);
    ChessMoveResponse knightMoves = __getKnightMoves(playerPieces);
    ChessMoveResponse bishopMoves = __getBishopMoves(playerPieces);
    ChessMoveResponse pawnMoves   = __getPawnMoves(playerPieces);
    
    ChessMoveResponse groupA = __combineChessMoveResponses(kingMoves, queenMoves);
    ChessMoveResponse groupB = __combineChessMoveResponses(rookMoves, knightMoves);
    ChessMoveResponse groupC = __combineChessMoveResponses(bishopMoves, pawnMoves);
    
    ChessMoveResponse groupD = __combineChessMoveResponses(groupA, groupB);
    
    return __combineChessMoveResponses(groupC, groupD);
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

    memcpy(moves, a.moves, sizeof(*moves) * a.totalMoves);
    memcpy(&moves[a.totalMoves], b.moves, sizeof(*moves) * b.totalMoves);

    destroyChessMoveResponse(a);
    destroyChessMoveResponse(b);

    return (ChessMoveResponse) {
        .moves=moves,
        .totalMoves=totalMoves,
    };
}

static PlayerPieces __getPlayerPieces(EngineState* state, PlayerColor playerColor) {
    switch (playerColor) {
        case WHITE:
            return (PlayerPieces) {
                .kings =   &state->bitBoard.whiteKings,
                .queens =  &state->bitBoard.whiteQueens,
                .rooks =   &state->bitBoard.whiteRooks,
                .knights = &state->bitBoard.whiteKnights,
                .bishops = &state->bitBoard.whiteBishops,
                .pawns =   &state->bitBoard.whitePawns,
            };

        case BLACK:
            return (PlayerPieces) {
                .kings =   &state->bitBoard.blackKings,
                .queens =  &state->bitBoard.blackQueens,
                .rooks =   &state->bitBoard.blackRooks,
                .knights = &state->bitBoard.blackKnights,
                .bishops = &state->bitBoard.blackBishops,
                .pawns =   &state->bitBoard.blackPawns,
            };
    }
}

static bool __isMoveEqual(ChessMove a, ChessMove b) {
    if (!___isChessSquareEqual(a.from, b.from)) {
        return false;
    }

    if (!___isChessSquareEqual(a.to, b.to)) {
        return false;
    }

    if (!___isChessPieceEqual(a.movedPieceType, b.movedPieceType)) {
        return false;
    }

    if (a.isCastling != b.isCastling) {
        return false;
    }

    if (a.isCastling) {
        if (!___isChessSquareEqual(a.castlingRookFrom, b.castlingRookFrom)) {
            return false;
        }

        if (!___isChessSquareEqual(a.castlingRookTo, b.castlingRookTo)) {
            return false;
        }
    }

    if (a.isTakingPiece != b.isTakingPiece) {
        return false;
    }

    if (a.isTakingPiece) {
        if (!___isChessPieceEqual(a.takenPiece, b.takenPiece)) {
            return false;
        }

        if (!___isChessSquareEqual(a.takenPiecePosition, b.takenPiecePosition)) {
            return false;
        }
    }

    return true;
}

static bool ___isChessSquareEqual(ChessSquare a, ChessSquare b) {
    return a.file == b.file && a.rank == b.rank;
}

static bool ___isChessPieceEqual(ChessPiece a, ChessPiece b) {
    return a.color == b.color && a.type == b.type;
}