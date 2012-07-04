<?php session_start();?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Brads Speaker Shop </title>
<meta name="Description" content="Brads speaker shop" />
<meta name="Keywords" content="css layout" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
<link rel="stylesheet" href="template.css" type="text/css" />
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
    
    	    
    	<h2>
    	Tannoy Revolution Signature Collection
    	</h2>
    	
    	<img  class="speaker" src="pictures/revolutionpack.jpg" alt="Tannoy Revolution Signature Collection picture"/>

    	<p>
  		Revolution Signature is pure escapism. A unique blend of aesthetic majesty and stunning acoustics with the power
  		and passion to transport you to an oasis of sanctuary far removed from today's hectic lifestyles. From the
  		compact stand-mount DC4 to the imposing yet elegant DC6, Revolution Signature will bring music to life in your
  		living room. Coupled with the horizontal DC4 LCR or DC6 LCR the range can be configured as a dynamic multi-
  		channel system with class-leading dynamics, power handling and efficiency. 	
		
		</p>

		<a  class="bigback" href="productlist_surround.php">Previous Page</a>

	</div>
	
      <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>