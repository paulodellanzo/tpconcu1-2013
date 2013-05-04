
mkdir temp
for ARCHIVO in $(ls ./src | grep ".cc" | sed s/.cc// )
do
	#make clean
	mv "./src/$ARCHIVO.cc" "./src/$ARCHIVO.cpp"
	make release
	mv "./src/$ARCHIVO.cpp" "./src/$ARCHIVO.cc"
	mv "./release/main" "./temp/$ARCHIVO"
done

for ARCHIVO in $(ls ./temp)
do
	mv "./temp/$ARCHIVO" "./release"
done
rmdir temp
	
