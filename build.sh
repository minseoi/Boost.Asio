EXECUTABLE_NAME="Run"
CURRENT_DIR=$(pwd)

# Boost
BOOST_PATH="/opt/homebrew/Cellar/boost/1.82.0_1"
BOOST_INCLUDE_PATH="$BOOST_PATH/include"
BOOST_LIB_PATH="$BOOST_PATH/lib"
BOOST_THREAD_LIB="boost_thread-mt"

# 컴파일 및 빌드 명령어
echo "Build start..."
if g++ -std=c++17 -I$BOOST_INCLUDE_PATH $(find Source -name "*.cpp") -L$BOOST_LIB_PATH -l$BOOST_THREAD_LIB -o $EXECUTABLE_NAME; then
    echo "Build succeeded\n"
    "$CURRENT_DIR/$EXECUTABLE_NAME" # 실행
else
    echo "Build failed"
fi
