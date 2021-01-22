using UnityEngine;
using UnityEngine.UI;

public class PlayerAim : MonoBehaviour
{
    public Transform headPos;

    private void Update()
    {
        RaycastHit hit;
        if (Physics.Raycast(headPos.position, headPos.TransformDirection(Vector3.forward), out hit, 5))
        {
            Debug.DrawRay(headPos.position, headPos.TransformDirection(Vector3.forward) * hit.distance, Color.yellow);

            float distance = Vector3.Distance(transform.position, hit.transform.position);
            if (distance <= 3f)
            {
                if (Input.GetMouseButtonDown(0))
                {
                    if (hit.transform.GetComponent<KeypadKey>() != null)
                    {
                        hit.transform.GetComponent<KeypadKey>().SendKey();
                    }
                }
            }
        }
    }
}

