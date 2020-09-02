# makefile for matrix

#### 頻繁に変更が必要なもの
# 実装のためのヘッダー(プロトタイム宣言、構造体宣言、定数定義を含む)
HEADER=matrix.h

# 作成したい関数が入ったファイル
OBJECTS= matrix.o

# 関数のテストが記載されたファイル(3年前期では使わない)
TEST_OBJECTS=

# 最終実行ファイル(名前を修正したら .gitignore も修正すること)
TARGET=matrixMain

# テスト実行ファイル(名前を修正したら .gitignore も修正すること)
TEST_TARGET=testMatrix

#### 以下は変更する必要がないもの

# 最終実行ファイルの実名
TARGET_EXE=$(TARGET)$(EXE)
# ターゲット実行ファイルの実名
TEST_TARGET_EXE=$(TEST_TARGET)$(EXE)
# 実装のメインファイル main 関数を含む
MAIN=$(TARGET).o
# テストのためのヘッダー(プロトタイプ宣言、3年前期では使わない)
#TEST_HEADER=$(TEST_TARGET).h
TEST_HEADER=
# テストのメインファイル main 関数を含む
TEST_MAIN=$(TEST_TARGET).o
# テストに必要なファイル
TEST_COMMON=testCommon.o
# 必要な CFLAGS
CFLAGS=-Wall -g
# 必要なライブラリ
LIBS=-lm
CHCP=

ifeq ($(OS),Windows_NT)
	CC=gcc
	RM=cmd.exe /C del
	EXE=.exe
	CHCP=chcp 65001
else
	RM=rm -f
	EXE=
endif

exec: $(TARGET_EXE) $(PNGS) $(SVGS)
test: $(TEST_TARGET_EXE)

$(TARGET_EXE): $(MAIN) $(OBJECTS) $(HEADER)
	$(CHCP)
	$(CC) -o $@ $(CFLAGS) $(MAIN) $(OBJECTS) $(LIBS)
	./$(TARGET_EXE)

$(TEST_TARGET_EXE): $(TEST_MAIN) $(OBJECTS) $(TEST_OBJECTS) $(TEST_COMMON) $(HEADER) $(TEST_HEADER)
	$(CHCP)
	$(CC) -o $@ $(CFLAGS) $(TEST_MAIN) $(OBJECTS) $(TEST_OBJECTS) $(TEST_COMMON) $(LIBS)
	./${TEST_TARGET_EXE}

clean:
	$(RM) $(TARGET_EXE) $(TEST_TARGET_EXE) $(MAIN) $(TEST_MAIN) $(OBJECTS) $(TEST_OBJECTS) $(TEST_COMMON)
