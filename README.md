# TowerDefense - TP final
## Taller de Programación I con Veiga
### 2do cuatrimestre de 2017
![](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/fiuba.png)
\
**Ayudante a cargo:** Martín Di Paola \
\
**Integrantes:** \
Martín Queija 96455 (tinqueija@gmail.com)\
Damián Cassinotti 96618 (damiancassinotti@gmail.com)\
Juan Pablo Rombolá 97131 (juampi.rombola@gmail.com)\
\
**Nota:** 10 (diez)
## El juego
El trabajo práctico de este cuatrimestre consistió en implementar una variante del clásico género Tower Defense, en donde varios enemigos emergen desde uno o varios portales y se mueven por caminos predefinidos y es el objetivo de los jugadores evitar que lleguen a destino.

Para tal fin, los jugadores deben cooperar entre sí y colocar torres de defensa que atacan automáticamente a los enemigos, así como también lanzar hechizos contra los enemigos directamente.

Los enemigos aparecen de a hordas cada cierto tiempo, dependiendo de cada nivel. Luego de haber acabado con todas las hordas, los jugadores logran la victoria; si al menos un enemigo logra llegar a destino los jugadores pierden.

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Torres.png "Vista al 06/11/17")

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Juego1.png "Vista nivel Easy")

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Juego2.png "Vista nivel Medium")

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Juego3.png "Vista nivel Insane")

## El editor de niveles
El juego cuenta con un editor de escenarios que permite crear cualquier tipo de mapa, configurando caminos, portales y hordas. Para más información ver el [Manual de usuario](https://github.com/JuampiRombola/TowerDefense/blob/master/Documentos/Manual%20de%20Usuario.pdf)

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Editor.png "Vista Editor")

## Instalación

1-​ ​Abrir​ ​una​ ​terminal​ ​en​ ​la​ ​raíz​ ​del​ ​juego\
2- Si no se poseen las dependencias (ver [Documentación Técnica](https://github.com/JuampiRombola/TowerDefense/blob/master/Documentos/Documentaci%C3%B3n%20T%C3%A9cnica.pdf)), ejecutar el archivo
install.sh​ ​con​ ​el​ ​comando​ ​ -i.​ Es decir: 
```
./install.sh​ -i
```
3-​ ​Una​ ​vez​ ​instaladas​ ​las​ ​dependencias,​ se debe ejecutar alguno de los siguientes comandos para instalar el juego:
```
./install.sh​ ​-c  // Instala ​solo​ ​el​ cliente
./install.sh​ ​-s  // ​Instala​ solo​ el​ servidor
./install.sh​ ​-e  // ​Instala ​solo​ ​el​ ​editor
./install.sh  // ​Instala​ todo
```
\
El​ juego​​ se​ instala​ en:
- /usr/local/games ​ ​ para​ ​los​​ ejecutables.
- /usr/local/etc/TowerDefense  ​ para​ los​ ​archivos​ de​ configuración y mapas.
- /usr/local/share/TowerDefense ​ ​ para​ ​los​ recursos​ como​ fuentes,​ sprites​ y sonidos.

## Más información
- [Manual de usuario](https://github.com/JuampiRombola/TowerDefense/blob/master/Documentos/Manual%20de%20Usuario.pdf)
- [Documentación Técnica](https://github.com/JuampiRombola/TowerDefense/blob/master/Documentos/Documentaci%C3%B3n%20T%C3%A9cnica.pdf)
- [Manual de proyecto](https://github.com/JuampiRombola/TowerDefense/blob/master/Documentos/Manual%20del%20Proyecto.pdf)