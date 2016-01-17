﻿#ifndef _CONFIG_H_
#define _CONFIG_H_

// --------------------
// release configurations
// --------------------

// --- 協力詰めエンジンとして実行ファイルを公開するとき用の設定集

#ifdef HELP_MATE_ENGINE
#undef ASSERT_LV
#define KEEP_LAST_MOVE
#undef  MAX_PLY_
#define MAX_PLY_ 65000
#undef HASH_KEY_BITS
#define HASH_KEY_BITS 128
#undef USE_EVAL_TABLE
#undef MATE_1PLY
#undef LONG_EFFECT
#endif

// --- 通常の思考エンジンとして実行ファイルを公開するとき用の設定集

#ifdef YANEURAOU_NANO_ENGINE
#undef ASSERT_LV
#undef KEEP_LAST_MOVE
#undef MATE_1PLY
#undef LONG_EFFECT
#endif

#ifdef YANEURAOU_MINI_ENGINE
#undef ASSERT_LV
#undef KEEP_LAST_MOVE
#undef MATE_1PLY
#undef LONG_EFFECT
#endif

#ifdef YANEURAOU_CLASSIC_ENGINE
#undef ASSERT_LV
#undef KEEP_LAST_MOVE
#endif

// --------------------
// include & configure
// --------------------

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <map>
#include <iostream>

// --- うざいので無効化するwarning
// C4800 : 'unsigned int': ブール値を 'true' または 'false' に強制的に設定します
// →　static_cast<bool>(...)において出る。
#pragma warning(disable : 4800)

// --- assertion tools

// DEBUGビルドでないとassertが無効化されてしまうので無効化されないASSERT
// 故意にメモリアクセス違反を起こすコード。
#define ASSERT(X) { if (!(X)) *(int*)0 =0; }

// ASSERT LVに応じたassert
#ifndef ASSERT_LV
#define ASSERT_LV 0
#endif

#define ASSERT_LV_EX(L, X) { if (L <= ASSERT_LV) ASSERT(X); }
#define ASSERT_LV1(X) ASSERT_LV_EX(1, X)
#define ASSERT_LV2(X) ASSERT_LV_EX(2, X)
#define ASSERT_LV3(X) ASSERT_LV_EX(3, X)
#define ASSERT_LV4(X) ASSERT_LV_EX(4, X)
#define ASSERT_LV5(X) ASSERT_LV_EX(5, X)

// --- switchにおいてdefaultに到達しないことを明示して高速化させる
#ifdef _DEBUG
// デバッグ時は普通にしとかないと変なアドレスにジャンプして原因究明に時間がかかる。
#define UNREACHABLE ASSERT_LV1(false);
#elif defined(_MSC_VER)
#define UNREACHABLE ASSERT_LV1(false); __assume(0);
#elif defined(__GNUC__)
#define UNREACHABLE __builtin_unreachable();
#else
#define UNREACHABLE ASSERT_LV1(false);
#endif

// PRETTY_JPが定義されているかどうかによって三項演算子などを使いたいので。
#ifdef PRETTY_JP
const bool pretty_jp = true;
#else
const bool pretty_jp = false;
#endif

#if HASH_KEY_BITS <= 64
#define HASH_KEY Key64
#elif HASH_KEY_BITS <= 128
#define HASH_KEY Key128
#else
#define HASH_KEY Key256
#endif

// ターゲットが64bitOSかどうか
#if defined(_WIN64) && defined(_MSC_VER)
const bool Is64Bit = true;
#else
const bool Is64Bit = false;
#endif

#endif // _CONFIG_H_
