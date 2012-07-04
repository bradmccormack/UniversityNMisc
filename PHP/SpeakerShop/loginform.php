<p>
    			Thank you for your interest in Hi Fidelity Sound. 
    			</p>
    
   	 			<p>
    			To take advantage of our bargain prices and high quality speakers please log in by entering your information below.
    			</p>
    	
    			<p>
    			Please use your email as your login name and yor first name as your password
    			</p>
    	
    			<div>
 					<form method=post > 
						<div>
							<input type="text" name="log" id="log" 
							value="<?php if(!empty($_POST['log']))
								echo $_POST['log']; ?>"/> Login <br/>
					
							<input type="text" name="password" id="password" 
							value="<?php if(!empty($_POST['password']))
								echo $_POST['password'] ?>"/> Password <br/>
	 				
							<input type="submit" value="login" name="login" />
						</div>
					</form>
				
					<?php require("loginverify.php"); ?>
		
				</div>
	 			<br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br />