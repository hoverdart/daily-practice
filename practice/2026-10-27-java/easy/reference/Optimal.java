public class Solution {
    public static class Node {
        public int value;
        public Node left, right;
        public Node(int value) { this.value = value; }
    }

    public static int closestThreshold(Node root, int target) {
        int best = root.value;
        Node current = root;
        while (current != null) {
            long gap = Math.abs((long) current.value - target);
            long bestGap = Math.abs((long) best - target);
            if (gap < bestGap || (gap == bestGap && current.value < best)) {
                best = current.value;
            }
            if (current.value == target) return target;
            current = current.value < target ? current.right : current.left;
        }
        return best;
    }
}
