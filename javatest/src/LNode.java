public class LNode
{
    private int m_info;
    private LNode m_link;

    public LNode(int info){
        m_info = info;
        m_link = null;
    }
    public void setLink(LNode link){
        m_link = link;
    }
    public LNode getLink(){
        return m_link;
    }
    public void setInfo(int info){
        m_info = info;
    }
    public int getInfo(){
        return m_info;
    }
}
