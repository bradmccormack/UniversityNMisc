<?php session_start();?>
<ul>
	<li class="button">
    		<a class="nav" href="index.php">Home</a>
    </li>
    <li class="button">
         	<a  class="nav" href="register.php">Register</a>
    </li>
    <li class="button">
          	<a  class="nav" href="productcategory.php">Products</a>
    </li>
    <li class="button">
          	<a  class="nav" href="privacypolicy.php">Privacy Policy</a>
    </li>   
    <?php
    //if the user is not logged in then set the button to login
    if($_SESSION['login']==false)
    	echo "<li class=\"button\"> <a  class=\"nav\" href=\"login.php\">Login</a> </li>";
    else
    {
    //otherwise set the button to logout and show member links
    	echo "<li class=\"button\"> <a class=\"nav\" href=\"logout.php\">Log Out</a> </li>";
    	    	echo "<li class=\"button\"> <a class=\"nav\" href=\"shoppingcart.php\">Shopping Cart</a> </li>";
    	//echo "<li class=\"button\"> <a class=\"nav\" href=\"SearchProducts.php\">Search Products</a> </li>";
    	//echo "<li class=\"button\"> <a class=\"nav\" href=\"Orders.php\">Orders</a> </li>";
    	//echo "<li class=\"button\"> <a class=\"nav\" href=\"Confirmation.php\">Confirmation</a> </li>";
    }	
    ?>
    <li class="button">
            <a  class="nav" href="sitemap.php">Site Map</a>
    </li>          
</ul>