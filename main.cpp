#include <stdio.h>
#include "BeautyBorder.h"
#include "Maze.h"
#include "Horizon.h"

BeautyBorder BB;

int main()
{
	Maze my_maze(3, 3);
	my_maze.print();
	Horizon h(Segment(-1., -1., 1., 1.));
  h.d_erase();
  h.d_push(Segment(-1., 0.5, -0.5, 0.));
  h.d_push(Segment(-0.5, 0.5, 0., 0.));
  h.d_push(Segment(-0.0, 0.5, 0.5, 0.));
  h.d_push(Segment(-0.5, 0.5, 1., 0.));

	h.add(Segment(-0.4, 0, 0.2, 0));

/*

	while (true) {
		Segment s(-1., -1., 1., 1.);
		printf("s : ");
		s.write(stdout);
		printf("\n enter pivot : ");
		Point p(0, 0);
		p.read(stdin);
		p.write(stdout);
		printf("\n");
		Point res = s.value(p);
		res.write(stdout);
		printf("\n");
	}
	*/
}
