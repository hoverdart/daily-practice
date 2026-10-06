public class TestSolution {
 static void check(int g,int e){if(g!=e)throw new AssertionError("got="+g+" expected="+e);}
 public static void main(String[] a){check(Solution.countNetworks(5,new int[][]{{0,1},{1,2},{3,4}}),2);check(Solution.countNetworks(4,new int[][]{}),4);check(Solution.countNetworks(1,new int[][]{}),1);check(Solution.countNetworks(6,new int[][]{{0,1},{1,2},{2,0},{4,5}}),3);check(Solution.countNetworks(0,new int[][]{}),0);System.out.println("All tests passed.");}
}
