
public class LinkedList
{
    private LNode head; // a reference to the first node
    // in the list
    public LinkedList()
    {
        head = null;
    }

    // This non-recursive method traverses the list and
    // count the total number of nodes and then save it
    // in the last node. You can assume that the list has
    // at least one node.
    // You will receive zero points if recursion is used.
    // For example, the following linked list on the left
    // has 3 nodes, so after this method is executed, the
    // list will be updated to the one on the right.



    public void saveCountinLastNode()
    {
        LNode curr = head;
        int count = 1;
        while(curr.getLink()!=null){
            curr = curr.getLink();
            count++;
        }
        curr.setInfo(count);
    }

    // This recursive method finds the node that has the
    // smallest even value.
    // You will receive zero points if any looping statements
    // are used.
    public int smallestEvenNode(LNode node)
    {
        if(node.getLink()==null){
            return node.getInfo();
        }else{
            if((node.getInfo() < node.getLink().getInfo() && node.getInfo()%2==0) || node.getLink().getInfo()%2!=0){
                node.setLink(node.getLink().getLink());
                return smallestEvenNode(node);
            }else{
                return smallestEvenNode(node.getLink());
            }
        }
    }
}