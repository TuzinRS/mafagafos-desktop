# Check runtime:
unameOut="$(uname -s)"

case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

echo Running on ${machine}!

# specific commands for:
if [[ "$machine" == "Linux" ]]; then # for Linux
	packagesNeeded='gcc build-essential libsdl2-dev libsdl2-image-dev'
	if [ -x "$(command -v apk)" ]; then
		sudo apk add --no-cache $packagesNeeded
 	elif [ -x "$(command -v apt-get)" ]; then
 		# APT-GET ONLY FOR COMPAT
 		sudo apt-get install $packagesNeeded
 	elif [ -x "$(command -v dnf)" ]; then
 		sudo dnf install $packagesNeeded
	elif [ -x "$(command -v zypper)" ]; then
		sudo zypper install $packagesNeeded
	else
		echo -e "\033[0;31mFAILED TO INSTALL PACKAGE: Package manager not found. You must manually install:\n\n\033[1;33m\033[1m$packagesNeeded\033[0;0m";
	fi
elif [[ "$machine" == "Mac" ]]; then # for MacOS
	$BREW=$(brew -v)
	if [[ $BREW == "-bash: brew: command not found" ]]; then
		echo -e "\033[1;33m\033[1mbrew not found, press Ctrl C to stop installation.\033[0;0m"
		/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
		bash ./install.sh
		rm ./install.sh
	fi
	brew install gcc sdl2_image
else # for Windows
	mkdir tmp
	$APT=$(wget -v)
	if [[ $APT == "bash: wget: command not found" ]]; then
		echo -e "\033[1;33m\033[1mwget not found, press Ctrl C to stop installation.\033[0;0m"
		curl https://downloads.sourceforge.net/project/unxutils/unxutils/current/UnxUtils.zip -L -s -o util.zip
		unzip -o util.zip -d /
		rm util.zip
	fi
	wget https://www.libsdl.org/release/SDL2-2.0.12-win32-x64.zip -O sdl2.zip
	wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5-win32-x64.zip -O sdl2_image.zip
	unzip -o sdl2_image.zip
	unzip -o sdl2.zip
	rm README-SDL.txt
	rm README.txt
	cp zlib1.dll build
	cp SDL2_image.dll build
	cp libwebp-7.dll build
	cp libtiff-5.dll build
	cp libpng16-16.dll build
	cp libjpeg-9.dll build
	cp SDL2.dll build
	rm sdl2.zip
	rm sdl2_image.zip
	
	#if is cygwin:
	if [[ $machine == "Cygwin" ]]; then
		cp /bin/Cygwin1.dll ./
		cp Cygwin1.dll build
	fi
	
	rm -Rf tmp
fi
