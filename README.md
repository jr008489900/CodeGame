# CodeGame-Mad-Pod

Hi! I'm happy to promote to gold league in this game.

https://www.codingame.com/ide/puzzle/mad-pod-racing

The main idea is to brake by push thrust at opposite direction.

The second you should notice is to compute the better path by this algorithm:
  for each checkpoint the target point at the circle side by this formula:
    x= x0 + r * cos(theta)
    y= y0 + r * sin(theta)  <- this may be wrong!! because there are som coordinate transformation.
    So y = y0 - r*sin(theta) is right.
    
Finally, in the gold league I might use the NeuroNetwork to solve the problem.
      

