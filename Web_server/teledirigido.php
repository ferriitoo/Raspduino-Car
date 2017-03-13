<html>
<head>
<title>
Coche teledirigido
</title>
<style>input[type="submit"] {
    background: url(var/www/html/indice.png);
    width: 130px; /* width of image */
    height: 120px; /* height of image */
    border: 1;
}
</style>
</head>
<body>
<hr>
<form action="" method="post">
<input type="submit" style="Position:Absolute; left:79%;top:15%;" name="aceleraratope" value="Aurrera Bizkor">
<input type="submit" style="Position:Absolute; left:65%;top:10%;" name="acelerarnormal" value="Aurrera Normal">
<input type="submit" style="Position:Absolute; left:51%;top:15%;" name="acelerarflojo" value="Aurrera Motel">
<input type="submit" style="Position:Absolute; left:65%;top:70%;" name="marchatras" value="Atzera">
<input type="submit" style="Position:Absolute; left:5%;top:50%;" name="izquierda" value="Ezkerra">
<input type="submit" style="Position:Absolute; left:33%;top:50%;" name="derecha" value="Eskuina">
<input type="submit" style="Position:Absolute; left:19%;top:50%;" name="recto" value="Zuzen">
<input type="submit" style="Position:Absolute; left:65%;top:40%;" name="frenar" value="Gelditu">


</form>
</body>
</html>
<?php
if (isset($_POST['aceleraratope']))
	exec ('sudo python /var/www/html/python/teledirigido/aceleraratope.py');

if (isset($_POST['frenar']))
        exec ('sudo python /var/www/html/python/teledirigido/detener.py');

if (isset($_POST['izquierda']))
        exec ('sudo python /var/www/html/python/teledirigido/izda.py');

if (isset($_POST['derecha']))
        exec ('sudo python /var/www/html/python/teledirigido/derecha.py');

if (isset($_POST['recto']))
        exec ('sudo python /var/www/html/python/teledirigido/recto.py');

if (isset($_POST['acelerarnormal']))
        exec ('sudo python /var/www/html/python/teledirigido/acelerarnormal.py');

if (isset($_POST['acelerarflojo']))
        exec ('sudo python /var/www/html/python/teledirigido/acelerarflojo.py');

if (isset($_POST['marchatras']))
        exec ('sudo python /var/www/html/python/teledirigido/marchatras.py');

?>
