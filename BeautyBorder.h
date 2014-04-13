#ifndef BEAUTYBORDER_H_INCLUDED
#define BEAUTYBORDER_H_INCLUDED

class BeautyBorder{
private:
	static const char ERR='E';
	//different types of borders
	static const int BMN=3;
	//number of square's sides
	static const int CONFIG_LENGTH=4;
	int n;
	char *a;
	int configToInt(const int config[]);
	int configToInt(int d0, int d1, int d2, int d3);
	int configToInt(const char config[]);
	void set(const char config[], const int val);
public:
	void testConvert();
	BeautyBorder(const char filename[]="");
	void open(const char filename[]="");
	char operator()(const char config[]);
	char operator()(int rht, int top, int lft, int btm);
	char operator()(int rht, int top, int lft, int btm, int err);
};

#endif // BEAUTYBORDER_H_INCLUDED
