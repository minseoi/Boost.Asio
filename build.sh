# 커스텀 실행파일 이름 설정
if [ $# -gt 0 ]; then
    EXECUTABLE_NAME="$1"
else
    EXECUTABLE_NAME="Run"
fi

# 현재 디렉토리 경로
CURRENT_DIR=$(pwd)

# Boost
BOOST_PATH="/opt/homebrew/Cellar/boost/1.82.0_1"
BOOST_INCLUDE_PATH="$BOOST_PATH/include"
BOOST_LIB_PATH="$BOOST_PATH/lib"
BOOST_THREAD_LIB="boost_thread-mt"

# 빌드 결과물 디렉토리 생성
BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# 컴파일 및 빌드 명령어
echo "Build start..."
if g++ -std=c++17 -I$BOOST_INCLUDE_PATH $(find Source -name "*.cpp") -L$BOOST_LIB_PATH -l$BOOST_THREAD_LIB -o "$BUILD_DIR/$EXECUTABLE_NAME"; then
    echo "Build succeeded\n"
    "$BUILD_DIR/$EXECUTABLE_NAME" # 실행
else
    echo "Build failed"
fi
