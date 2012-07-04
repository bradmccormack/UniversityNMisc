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
    	Bowers and Wilkins CM Collection
    	</h2>
    	
    	<img  class="speaker" src="pictures/CMpack.jpg" alt="Bowers and Wilkins Collection picture"/>

    	<p>
  		By using our most refined drive unit technologies, developed for reference-standard speakers such as
  		the 800 Series Diamond, we've been able to hone the speaker down to its purest essentials. The CM Series
  		uses minimalist crossovers of remarkable simplicity and quality, so what you hear is that much closer to
  		the sound of the original recording. In its functional perfection and understated elegance, it's nothing less
  		than a masterpiece. Pure and simple.
		</p>

		<a  class="bigback" href="productlist_surround.php">Previous Page</a>

	</div>
	
      <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>