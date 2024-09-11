import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Solution solution = new Solution();

        List<Integer> tree1Array = new ArrayList<>();
        tree1Array.add(1);
        tree1Array.add(2);
        tree1Array.add(3);
        tree1Array.add(4);
        tree1Array.add(5);
        tree1Array.add(6);

        TreeNode tree1 = solution.createTreeFromArray(tree1Array);

        List<Integer> tree2Array = new ArrayList<>();
        tree2Array.add(1);
        tree2Array.add(2);
        tree2Array.add(3);
        tree2Array.add(4);
        tree2Array.add(5);

        TreeNode tree2 = solution.createTreeFromArray(tree2Array);

        boolean result = solution.isSameTree(tree1, tree2);

        System.out.println(result);
    }

    static class TreeNode{
        int val;
        TreeNode left, right;

        TreeNode(int x){
            this.val = x;
            this.left = null;
            this.right = null;
        }
    }

    static class Solution {
        public boolean isSameTree (TreeNode p, TreeNode q){
                if (p == null && q == null) return true;
                if (p == null || q == null) return false;
                if (p.val != q.val) return false;
                return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
        }
        public TreeNode arrayToTree(List<Integer> list, int index) {
            if (index >= list.size() || list.get(index) == null) {
                return null;
            }
            TreeNode node = new TreeNode(list.get(index));
            node.left = arrayToTree(list, 2 * index + 1);  // Left child
            node.right = arrayToTree(list, 2 * index + 2); // Right child
            return node;
        }
        public TreeNode createTreeFromArray(List<Integer> arr) {
            return arrayToTree(arr, 0);
        }
    }


}
