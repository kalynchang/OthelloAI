Describe how and what each group member contributed for the past two weeks. If you are solo, these points will be part of the next section.

Week 9
We met up before the Sunday extra credit deadline and learned how to use bitbucket. Then on Sunday night we met up again to implement a working AI that played random moves. It worked. We started discussing how we could implement a heuristic function. On Monday night we met up to add a heuristic function so that our AI beat SimplePlayer consistently. We managed to beat SimplePlayer 9/10 times. We pushed our changes and turned in our assignment because we weren't able to figure out how to implement the minimax decision tree on time. We did all of the work together at the same time.

Week 10  
We met on Thursday to work on implementing the minimax decision tree. We outlined it. On Saturday we implemented it. On Sunday we got it to compile. We tried it on the ConstantTimePlayer but it only worked half the time. Like the previous week, we worked on everything together at the same time. 

Document the improvements that your group made to your AI to make it tournament-worthy. Explain why you think your strategy(s) will work. Feel free to discuss any ideas were tried but didn't work out.

To make our AI tournament-worthy, we used a 4-ply minimax decision tree instead of a 2-ply one. For our heuristic function, we multiplied the corner values by 3 and the places adjacent to the corners by -3. Our starting value was the number of tiles the we would have minus the number of tiles the opponent would have. We also tested all the different complier optimization levels and decided on -03. We felt that our AI performed best at that optimization level.


