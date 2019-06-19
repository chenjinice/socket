#/bin/bash


qt4_lib=`dpkg -L fcitx-frontend-qt4 | grep .so`
qt5_lib=`dpkg -L fcitx-frontend-qt5 | grep .so`

dir1=/home/duser/Qt5.5.0/Tools/QtCreator/bin/plugins/platforminputcontexts/
dir2=/home/duser/Qt5.5.0/5.5/gcc/plugins/platforminputcontexts/

echo "qt4_lib = ${qt4_lib}"
echo "qt5_lib = ${qt5_lib}"

if [ -n ${qt5_lib} ];then
	sudo chmod +x ${qt5_lib}
	cp ${qt5_lib} ${dir1}
	cp ${qt5_lib} ${dir2}
fi

if [ -n ${qt4_lib} ];then
	sudo chmod +x ${qt4_lib}
	cp ${qt4_lib} ${dir1}
	cp ${qt4_lib} ${dir2}
fi



