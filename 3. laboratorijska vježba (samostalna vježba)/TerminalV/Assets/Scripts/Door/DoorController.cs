using UnityEngine;

public class DoorController : MonoBehaviour
{
    private Animator doorAnim;
    private bool doorOpen = false;

    public bool doorUnlocked = false;

    public string open;
    public string close;

    public bool closeDoorOnStart;

    private void Start()
    {
        if (closeDoorOnStart)
        {
            doorAnim.Play(close, 0, 0.0f);
            doorOpen = false;
        }
    }

    private void Awake()
    {
        doorAnim = gameObject.GetComponent<Animator>();
    }

    public void PlayAnimation()
    {
        if (doorUnlocked == true)
        {
            if (!doorOpen)
            {
                doorAnim.Play(open, 0, 0.0f);
                doorOpen = true;
                Debug.Log("Opening");
            }
            else
            {
                doorAnim.Play(close, 0, 0.0f);
                doorOpen = false;
                Debug.Log("Closing");
            }
        }
    }
}
