public class testSplit {
public static void main(String[] args) {
	System.out.println(args[0]);
	String str = args[0];
	String[] split = str.split("/");
	for(String s : split) {
		System.out.println(s);
	}
}
}
