(func fibonacci(n)
   (cond (equal 0 n) 0    
	(cond (equal 1 n) 1 
		(plus (fibonacci (minus n 1) (fibonacci(minus n 2)))))))