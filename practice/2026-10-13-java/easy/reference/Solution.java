import java.util.ArrayDeque;
import java.util.Queue;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int val) { this.val = val; }
}

public class Solution {
    public static int deepestLeftmost(TreeNode root) {
        if (root == null) return -1;
        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.add(root);
        int answer = root.val;
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.remove();
                if (i == 0) answer = node.val;
                if (node.left != null) queue.add(node.left);
                if (node.right != null) queue.add(node.right);
            }
        }
        return answer;
    }
}
