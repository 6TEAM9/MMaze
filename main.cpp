#include <stdio.h>
#include "BeautyBorder.h"
#include "Maze.h"
#include "Horizon.h"

BeautyBorder BB;

int main()
{
	Maze my_maze(3, 3);
	my_maze.generate(3);
	my_maze.print('X', '0');
//	Horizon h(Segment(-1., -1., 1., 1.));
//  h.d_erase();
//  h.d_push(Segment(-1., 0.5, -0.5, 0.));
//  h.d_push(Segment(-0.5, 0.5, 0., 0.));
//  h.d_push(Segment(-0.0, 0.5, 0.5, 0.));
//  h.d_push(Segment(-0.5, 0.5, 1., 0.));

//	h.add(Segment(-0.4, 0, 0.2, 0));
/*(
	while (true) {
		Segment first(-1, 0, 1, 0.5);
		first.write(stdout);
		printf("\n");
		Segment second(0, 0, 0, 0);
		printf("Enter segment : \n");
		second.read(stdin);
		Point p = first.intersection(second);
		printf("Result : ");
		p.write(stdout);
		printf("\n");
	}
*/
	Horizon hz(Segment(-1, -1, 1, 1));
	while (true) {
		hz.clear();
		hz.print();
		printf("Enter segment : \n");
		Segment s(0, 0, 0, 0);
		s.read(stdin);
		s.write(stdout);
		printf("\n-------------------------\n");
		hz.add(s);
		hz.print();
		char c;
		scanf("%c", &c);
		printf("-------------------------\n");
	}
}
