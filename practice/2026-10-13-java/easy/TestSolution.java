import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class TestSolution {
    private static int checked = 0;
    private static void check(int actual, int expected) {
        if (actual != expected) throw new AssertionError("Expected " + expected + " but got " + actual);
        checked++;
    }
    private static int oracle(TreeNode root) {
        if (root == null) return -1;
        List<TreeNode> level = new ArrayList<>();
        level.add(root);
        int result = root.val;
        while (!level.isEmpty()) {
            result = level.get(0).val;
            List<TreeNode> next = new ArrayList<>();
            for (TreeNode node : level) {
                if (node.left != null) next.add(node.left);
                if (node.right != null) next.add(node.right);
            }
            level = next;
        }
        return result;
    }
    private static TreeNode randomTree(Random rng, int size) {
        if (size == 0) return null;
        TreeNode root = new TreeNode(rng.nextInt(2001) - 1000);
        List<TreeNode> candidates = new ArrayList<>();
        candidates.add(root);
        for (int i = 1; i < size; i++) {
            TreeNode node = new TreeNode(rng.nextInt(2001) - 1000);
            int pos = rng.nextInt(candidates.size());
            TreeNode parent = candidates.get(pos);
            if (parent.left == null && parent.right == null) {
                if (rng.nextBoolean()) parent.left = node; else parent.right = node;
            } else if (parent.left == null) parent.left = node;
            else parent.right = node;
            if (parent.left != null && parent.right != null) candidates.remove(pos);
            candidates.add(node);
        }
        return root;
    }
    public static void main(String[] args) {
        check(Solution.deepestLeftmost(null), -1);
        check(Solution.deepestLeftmost(new TreeNode(-7)), -7);
        TreeNode root = new TreeNode(10);
        root.left = new TreeNode(20); root.right = new TreeNode(30);
        root.left.left = new TreeNode(40); root.right.right = new TreeNode(50);
        check(Solution.deepestLeftmost(root), 40);
        root.right.right.left = new TreeNode(60);
        check(Solution.deepestLeftmost(root), 60);
        Random rng = new Random(61013);
        for (int i = 0; i < 350; i++) {
            TreeNode t = randomTree(rng, rng.nextInt(90));
            check(Solution.deepestLeftmost(t), oracle(t));
        }
        TreeNode chain = new TreeNode(0), current = chain;
        for (int i = 1; i <= 1500; i++) {
            current.right = new TreeNode(i);
            current = current.right;
        }
        check(Solution.deepestLeftmost(chain), 1500);
        System.out.println("PASS easy: " + checked + " checks");
    }
}
