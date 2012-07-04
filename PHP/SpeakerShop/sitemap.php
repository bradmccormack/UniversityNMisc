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
    
    <p class="sitemap">
    Sitemap for Hi Fidelity Sound
    </p>   
 
   	<ul class="sitemap">
		<li >
    		<a  href="index.php">Home</a>
    	</li>
    	<li >
         	<a  href="register.php">Register</a>
    	</li>
    	<li >
          	<a  href="productcategory.php">Products</a>
          	
          	<!--next level deep -->
   			<ul class="sitemapsub">
				<li>
					<a href="productlist_stereo.php"> Stereo / 2 Channel Products</a>
					<!--next level deep -->
					<ul class="sitemapsub">
					
					<li>
						<a href="productdetail_bowers800diamond.php"> Bowers and Wilkins 800 Diamond</a>
					</li>
					
					<li>
						<a href="productdetail_tannoydimension.php"> Tannoy Dimension DC8T</a>
					</li>
					
					</ul>
				</li>
					
				<li>
					<a href="productlist_surround.php"> Surround / 5.1 Channel Products</a>
					<!--next level deep -->
					<ul class="sitemapsub">
					
					<li>
						<a href="productdetail_revolutionpack.php"> Tannoy Revolution Signature Pack</a>
					</li>
					
					<li>
						<a href="productdetail_cmpack.php"> Bowers and Wilkins CM Pack</a>
					</li>
					
					</ul>
				</li>

			</ul>
		</li>
			
    	<li>
          	<a  href="privacypolicy.php">Privacy Policy</a>
    	</li>
    	
    	<li >
            <a   href="login.php">Login</a>
    	</li>
    
    	<?php
    	//only show the shopping cart in the sitemap if they are logged in
    	if($_SESSION['login']==true)
    		echo "<li> <a href=shoppingcart.php>Shopping cart</a>";
    		
    	?>
    	
    	
    	
    	
    	<li>
            <a   href="sitemap.php">Site Map</a>
    	</li>          
	</ul>
	<br /><br /><br /><br /><br /><br />
	     
</div>
  <div id="footer">
    	<?php require("footer.php"); ?>
    </div>

</div>


    
</body>
</html>