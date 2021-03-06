<?php session_start(); ?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">

<head>
	<title>Brads Speaker Shop - Login</title>
	<meta name="Description" content="Brads speaker shop" />
	<meta name="Keywords" content="css layout" />
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
	<link rel="stylesheet" href="template.css" type="text/css" />
	<script type="text/javascript" src="validate.js"> </script>
</head>
<body>
	
<div id="wrapper">
    <div id="header">
          <?php require("header.php");?>
    </div>

    <div id="nav">
    	<?php require("navbar.php");?>
    </div>
    
    <div id="main">
    	
    	<?php
    		if($_SESSION['login']==false)
    		{
    			//user has not logged in so show the correct form
    			require "loginform.php";
	 		}
	 		else
	 		{
	 			//user is currently logged in so show a message about logging out
	 			echo "We hope you enjoy your shopping ".$_SESSION['name'].'! <br> <br>';
	 			echo "Click Log out when you have finished shopping.";
	 			echo "<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>";
	 		}
	 		
		?>
	</div>
	
     <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>