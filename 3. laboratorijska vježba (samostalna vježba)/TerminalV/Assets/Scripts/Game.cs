using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class Game : MonoBehaviour
{
    [SerializeField] public static int keysCollected;
    public TMP_Text textDisplay;

    // Start is called before the first frame update
    void Start()
    {
        keysCollected = 0;
    }

    // Update is called once per frame
    void Update()
    {
        UpdateKeysUI();
    }

    public void UpdateKeysUI()
    {
      textDisplay.text = keysCollected + "/5";
    }
}
