function installDependencies() {
    echo 'Instalando dependencias' >&2
    sudo apt-get install libsdl2-dev
    sudo apt-get install libsdl2-image-dev
    sudo apt-get install libsdl2-ttf-dev
    sudo apt-get install libsdl2-mixer-dev
    sudo apt-get install libgtk-3-dev
    sudo apt-get install libgtkmm-3.0-dev
    sudo apt-get install libboost-dev
    sudo apt-get install libyaml-cpp-dev
    sudo apt-get install cmake
}

function startCompiling() {
    cmake CMakeLists.txt
}

function compileServer() {
    echo 'Instalando TowerDefenseClient' >&2
    make TowerDefenseServer
    sudo mv TowerDefenseServer /usr/bin
}

function compileClient() {
    echo 'Instalando TowerDefenseClient' >&2
    make TowerDefenseClient
    sudo mv TowerDefenseClient /usr/bin
}

function compileEditor() {
    echo 'Instalando TowerDefenseEditor' >&2
    make TowerDefenseEditor
    sudo mv TowerDefenseEditor /usr/bin
}

function clean() {
    rm -rf CMakeFiles
    rm -f CMakeCache.txt cmake_install.cmake Makefile
}

function moveConfigAndResources() {
    if [ ! -d /etc/TowerDefense ]; then
      sudo mkdir /etc/TowerDefense
    fi
    sudo cp -a Resources /etc/TowerDefense
    sudo cp -a config/* /etc/TowerDefense
}

case $1 in
-i)
    installDependencies
    exit 0
  ;;
-s)
    startCompiling
    compileServer
    moveConfigAndResources
    clean
    exit 0
  ;;
-c)
    startCompiling
    compileClient
    moveConfigAndResources
    clean
    exit 0
  ;;
-e)
    startCompiling
    compileEditor
    moveConfigAndResources
    clean
    exit 0
  ;;
--help | -h | \?)
    echo "Help:
    Sin opciones instala el servidor, cliente y editor y configura los archivos. NO SE INSTALARAN DEPENDENCIAS.
    -i para instalar dependencias
    -c para instalar el cliente
    -s para instalar el servidor
    -e para instalar el editor
    -conf para configurar el ambiente" >&2
    exit 0
    ;;
esac

startCompiling
compileServer
compileEditor
compileClient
moveConfigAndResources
clean
exit 0
