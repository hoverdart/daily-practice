import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.TreeSet;

public class TestSolution {
    private static int checks = 0;
    private static void eq(int actual, int expected) {
        if (actual != expected) throw new AssertionError("expected " + expected + ", got " + actual);
        checks++;
    }

    private static Solution.Node insert(Solution.Node root, int value) {
        if (root == null) return new Solution.Node(value);
        Solution.Node p = root;
        while (true) {
            if (value < p.value) {
                if (p.left == null) { p.left = new Solution.Node(value); break; }
                p = p.left;
            } else if (value > p.value) {
                if (p.right == null) { p.right = new Solution.Node(value); break; }
                p = p.right;
            } else break;
        }
        return root;
    }

    private static int oracle(TreeSet<Integer> values, int target) {
        int best = values.first();
        for (int x : values) {
            long gap = Math.abs((long) x - target);
            long bestGap = Math.abs((long) best - target);
            if (gap < bestGap || (gap == bestGap && x < best)) best = x;
        }
        return best;
    }

    public static void main(String[] args) {
        Solution.Node root = null;
        for (int x : new int[]{6, 2, 8, 4}) root = insert(root, x);
        eq(Solution.closestThreshold(root, 5), 4);
        eq(Solution.closestThreshold(root, 6), 6);
        eq(Solution.closestThreshold(root, -500), 2);
        eq(Solution.closestThreshold(root, 500), 8);
        eq(Solution.closestThreshold(new Solution.Node(42), -100), 42);
        Solution.Node extreme = insert(null, Integer.MIN_VALUE);
        insert(extreme, Integer.MAX_VALUE);
        eq(Solution.closestThreshold(extreme, 0), Integer.MAX_VALUE);
        eq(Solution.closestThreshold(extreme, Integer.MIN_VALUE), Integer.MIN_VALUE);

        Random random = new Random(20261027);
        for (int trial = 0; trial < 650; trial++) {
            int n = 1 + random.nextInt(120);
            TreeSet<Integer> values = new TreeSet<>();
            while (values.size() < n) values.add(random.nextInt(2001) - 1000);
            List<Integer> order = new ArrayList<>(values);
            Collections.shuffle(order, random);
            Solution.Node tree = null;
            for (int x : order) tree = insert(tree, x);
            for (int j = 0; j < 5; j++) {
                int target = random.nextInt(3001) - 1500;
                eq(Solution.closestThreshold(tree, target), oracle(values, target));
            }
        }
        Solution.Node chain = new Solution.Node(0);
        Solution.Node p = chain;
        for (int i = 1; i < 100_000; i++) {
            p.right = new Solution.Node(i);
            p = p.right;
        }
        eq(Solution.closestThreshold(chain, 75_321), 75_321);
        eq(Solution.closestThreshold(chain, -3), 0);
        eq(Solution.closestThreshold(chain, 150_000), 99_999);
        System.out.println("PASS easy: " + checks + " checks");
    }
}
