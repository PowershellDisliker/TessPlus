#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_MOVABLE_PIECES_PER_TURN 2

typedef enum ChessRank {
    RANK_A,
    RANK_B,
    RANK_C,
    RANK_D,
    RANK_E,
    RANK_F,
    RANK_G,
    RANK_H,
} ChessRank;

typedef enum ChessFile {
    FILE_1,
    FILE_2,
    FILE_3,
    FILE_4,
    FILE_5,
    FILE_6,
    FILE_7,
    FILE_8,
} ChessFile;

typedef enum ChessPiece {
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_PAWN,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_PAWN,
    EMPTY,
} ChessPiece;

typedef enum PlayerColor {
    WHITE,
    BLACK,
} PlayerColor;

typedef struct ChessSquare {
    ChessRank rank;
    ChessFile file;
} ChessSquare;

typedef struct ChessMove {
    size_t totalPiecesMoved;

    ChessSquare from[MAX_MOVABLE_PIECES_PER_TURN];
    ChessSquare to[MAX_MOVABLE_PIECES_PER_TURN];
} ChessMove;

typedef struct ChessMoveResponse {
    size_t totalMoves;
    ChessMove* moves;
} ChessMoveResponse;

typedef struct BitBoards {
    uint64_t whiteKings;
    uint64_t whiteQueens;
    uint64_t whiteRooks;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whitePawns;

    uint64_t blackKings;
    uint64_t blackQueens;
    uint64_t blackRooks;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackPawns;
} BitBoards;

typedef struct ChessFlags {
    bool whiteCanCastle;
    bool blackCanCastle;


} ChessFlags;

typedef struct EngineState {
    PlayerColor currentPlayer;
    BitBoards bitBoard;
    ChessFlags flags;
    size_t maximumMoveCount;
    size_t moveCount;
    ChessMove* moves;
} EngineState;

typedef struct BoardState {
    ChessPiece squares[64];
} BoardState;

typedef struct EngineResponse {
    bool success;
    bool winnerExists;
    PlayerColor winner;
} EngineResponse;

// Memory
void initializeEngineState(EngineState*, const size_t);
void destroyEngineState(EngineState*);

void destroyChessMoveResponse(ChessMoveResponse);

// Logic
ChessMoveResponse getMoves(EngineState*);
EngineResponse makeMove(EngineState*, ChessMove);
EngineResponse undoMove(EngineState*);
void getBoardState(EngineState*, BoardState*);