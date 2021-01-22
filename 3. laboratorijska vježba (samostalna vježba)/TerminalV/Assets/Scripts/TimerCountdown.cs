using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class TimerCountdown : MonoBehaviour
{
    public TMP_Text textDisplay;
    public static int secondsLeft = 1200;
    public bool takingAway = false;
    int minutesLeft;
    public MyDoorController door;

    // Start is called before the first frame update
    void Start()
    {
        minutesLeft = secondsLeft / 60;
        if(minutesLeft >= 1 && minutesLeft > 9)
        {
            textDisplay.text = minutesLeft + ":00";
        }
        else if (minutesLeft <= 9 && secondsLeft > 59)
        {
            textDisplay.text = "0" + minutesLeft + ":00";
        }
        else
        {
            textDisplay.text = "00:" + secondsLeft;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(takingAway == false && secondsLeft > 0 && door.doorUnlocked == true)
        {
            StartCoroutine(TimerTake());
        }    
    }

    IEnumerator TimerTake()
    {
        takingAway = true;
        yield return new WaitForSeconds(1);

        secondsLeft -= 1;
        minutesLeft = secondsLeft / 60;
        if (secondsLeft < 10)
        {
            textDisplay.text = "00:0" + secondsLeft;
        }
        else if(secondsLeft < 60)
        {
            textDisplay.text = "00:" + secondsLeft;
        }
        else if(minutesLeft > 9)
        {
            if (secondsLeft % 60 >= 10)
            {
                textDisplay.text = minutesLeft + ":" + secondsLeft % 60;
            }
            else
            {
                textDisplay.text = minutesLeft + ":" + "0" + secondsLeft % 60;
            }
        }
        else
        {
            if (secondsLeft % 60 >= 10)
            {
                textDisplay.text = "0" + minutesLeft + ":" + secondsLeft % 60;
            }
            else
            {
                textDisplay.text = "0" + minutesLeft + ":" + "0" + secondsLeft % 60;
            }
        }
        takingAway = false;
    }
}
