APP_NAME="mafagafight"
APP_VERSION="1.0.0"
APP_CHANNEL="alpha"

################################################################################
# PLEASE DO NOT EDIT BELOW UNLESS YOU KNOW WHAT YOU ARE DOING!                 #
#                                                                              #
# Some changes may cause wrong compilation, so please be careful.              #
################################################################################

APP="$APP_NAME"
FLAGS=

# Check runtime:
unameOut="$(uname -s)"

case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

# Add runtime specific flags:
if [[ "$machine" == "Linux" ]]; then
	FLAGS="-lpthread $FLAGS"
fi

echo Running on ${machine}!

# List sources:
cd src
SOURCES=$(find  . -name \*.c -print | sed -s "s/^/src\//" | sed "s/\\.\\///")
cd ..

# [UNUSED] List outputs:
cd src
OUTPUT=$(find  . -name \*.c -print | sed -s "s/^/out\//" | sed "s/.c/.o/" | sed "s/\\.\\///")
cd ..

gcc $SOURCES -o build/$APP $FLAGS -lSDL2 -lSDL2_image -lGL -Iincludes
#ld  $OUTPUT -o build/$APP -lSDL2 -lGL #CASO DE ERRO COM MULTIPLOS ARQUIVOS, DESCOMENTE ESSA LINHA
chmod 777 build/$APP
