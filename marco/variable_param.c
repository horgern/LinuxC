#include <stdio.h>
#include <unistd.h>
#define my_print1(...)  printf(__VA_ARGS__)   

#define my_print2(fmt,...)  printf(fmt,__VA_ARGS__)  
//这个比起上面的那个，好处就是当可变参数为空时，会把 , 去掉，否则会报错
#define my_print3(fmt,...)  printf(fmt,##__VA_ARGS__)  
void __VA_ARGES__Test()
{
	int i = 1, j = 2;
	my_print1("i=%d,j=%d\n",i,j);// 正确打印
	my_print2("i=%d\n",i);// 正确打印
	//my_print2("false\n");// 正确打印
	my_print3("true\n");// 正确打印
}

////////////////////////////////////////////////////
/* double well usage (1) */
void ForTestChar()
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	
}

void ForTestInt()
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	
}

void ForTestLong()
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	
}

#define ForTest(TYPE) ForTest##TYPE()

void DoubleWellTest()
{
	ForTest(Char);
	ForTest(Int);
	ForTest(Long);
}
/////////////////////////////////////////////////////////////////
/* double well usage (2) */
void ForTestCharT(int n)
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	printf("n = [%d]\n", n);
}

void ForTestIntT(int n)
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	printf("n = [%d]\n", n);
}

void ForTestLongT(int n)
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	printf("n = [%d]\n", n);
}

void ForTestStrT(char *n)
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	printf("n = [%s]\n", n);
}

void ForTestNumStrT(char     *n)
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
	printf("n = [%s]\n", n);
}


//这里有个地方，就是##T，为什么呢，不加的话会变成##TYPET
//用一个# 是不行的
//而且，需要注意的地方是，## 和 # 一起使用，容易出现问题
#define TestFor(TYPE, n) ForTest##TYPE##T(n)

//这里#n 表示字符串的意思，
#define TFor(TYPE, n) ForTest##TYPE##T(#n)



//加不加这个都不会出错，只是为了显示方便
enum Type {
	Char = 0,
	Int = 1,
	Long = 2,
};


void DoubleWellTest02()
{
	TestFor(Char, 1);
	TestFor(Int, 2);
	TestFor(Long, 3);

	//以下两个函数相比，就可以知道不加# 号更加灵活，加了#，就表示字符串
	TFor(Str, 456);
	TestFor(NumStr, "789");
}

//////////////////////////////////////////////////
/* single well usage  */
#define debug(INFO) \
			printf("\n[%s-%d] ============== [%s] ==============\n", __func__, __LINE__, #INFO)

//安照使用习惯来看，还是下面这个比较符合实际情况，我们常用的字符串，是需要加“” 
//再进一步看，宏定义的参数很方便，在（）里面写，后面直接替换
#define debug1(INFO) \
			printf("\n[%s-%d] ============== [%s] ==============\n", __func__, __LINE__, INFO)

void SingleWellTest()
{
	debug(test);
	//debug1(test);	//"这样有问题"
	debug1("test");

	debug("hello");
	debug1("hello");

	printf("\n[%s-%d] ============== [%s] ==============\n", __func__, __LINE__, "hello");
}





int main(int arg, char **argv)
{
	if (arg != 2) {
		printf("Usage is not right!\n");
		return -1;
	}
	switch(atoi(argv[1])) {
	case 1:
		__VA_ARGES__Test();
		break;
	case 2:
		DoubleWellTest();
		break;
	case 3:
		DoubleWellTest02();
		break;
	case 4:
		SingleWellTest();
		break;
	}
	

}
