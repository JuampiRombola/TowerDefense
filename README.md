# TowerDefense - TP final [FIUBA]
## Taller de Programación I con Veiga
### 2do cuatrimestre de 2017
\
**Ayudante a cargo:** Martín Di Paola \
\
**Integrantes:** \
Martín Queija 96455 \
Damián Cassinotti 96618 \
Juan Pablo Rombolá 97131 \
\
**Nota:** 10 (diez)
\
\
## El juego
El trabajo práctico de este cuatrimestre consistió en implementar una variante del clásico género Tower Defense, en donde varios enemigos emergen desde uno o varios portales y se mueven por caminos predefinidos hacia su destino y es el objetivo de los jugadores evitar que lleguen a destino. \
Para tal fin, los jugadores deben cooperar entre sí y colocar torres de defensa que atacan automáticamente a los enemigos, así como también lanzar hechizos contra los enemigos directamente.\
Los enemigos aparecen de a hordas cada cierto tiempo, dependiendo de cada nivel. Luego de haber acabado con todas las hordas, los jugadores logran la victoria; si al menos un enemigo logra llegar a destino los jugadores pierden.

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Torres.png "Vista al 06/11/17")

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Juego1.png "Vista nivel Easy")

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Juego2.png "Vista nivel Medium")

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Juego3.png "Vista nivel Insane")

## El editor de niveles

![alt text](https://github.com/JuampiRombola/TowerDefense/blob/master/Resources/Editor.png "Vista Editor")

## Instalación

1-​ ​ Abrir​ ​ una​ ​ terminal​ ​ en​ ​ la​ ​ raíz​ ​ del​ ​ juego
2- Si no posee las dependencias (Ver Documentación Técnica), debe ejecutar el archivo
install.sh​ ​ con​ ​ el​ ​ comando​ ​ -i.​ ​ 
De​ ​ esta​ ​ forma,​ ​ el​ ​ comando​ ​ a ​ ​ ejecutar​ ​ quedará​ ​ 
```
./install.sh​ ​ -i
```
3-​ ​ Una​ ​ vez​ ​ instaladas​ ​ las​ ​ dependencias,​ ​ debe:
3.1-​ ​ Si​ ​ quiere​ ​ instalar​ ​ solo​ ​ el​ ​ cliente,​ ​ ejecute​
```
./install.sh​ ​ -c
```
3.2-​ ​ Si​ ​ quiere​ ​ instalar​ ​ solo​ ​ el​ ​ servidor,​ ​ ejecute​ ​ 
```
./install.sh​ ​ -s
3.3-​ ​ Si​ ​ quiere​ ​ instalar​ ​ solo​ ​ el​ ​ editor,​ ​ ejecute​ ​ 
```
./install.sh​ ​ -e
```
3.1-​ ​ Si​ ​ quiere​ ​ instalar​ ​ todo,​ ​ ejecute​ ​ 
```
./install.sh
```
\
El​ ​ juego​ ​ se​ ​ instala​ ​ en:
● /usr/local/games ​ ​ para​ ​ los​ ​ ejecutables
● /usr/local/etc/TowerDefense ​ ​ para​ ​ los​ ​ archivos​ ​ de​ ​ configuración
● /usr/local/share/TowerDefense ​ ​ para​ ​ los​ ​ recursos​ ​ como​ ​ fuentes,​ ​ sprites​ ​ y ​ ​ sonidos.

# [Manual de usuario](https://github.com/JuampiRombola/TowerDefense/blob/master/Documentos/Manual\ de\ Usuario.pdf)