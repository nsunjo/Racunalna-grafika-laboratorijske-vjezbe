using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using UnityEngine;

public class LightFlash : MonoBehaviour
{
    Light light;

    private bool flashOnStart = true;
    private bool repeat = true;

    private char[] letters = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
    private string[] morseLetters = { "    ", ". _", "_ . . .", "_ . _ .", "_ . .", ".", ". . _ .", "_ _ .", ". . . .", ". .", ". _ _ _", "_ . _", ". _ . .", "_ _", "_ .", "_ _ _", ". _ _ .", "_ _ . _", ". _ .", ". . .", "_", ". . _", ". . . _", ". _ _", "_ . . _", "_ . _ _", "_ _ . .", ". _ _ _ _", ". . _ _ _", ". . . _ _", ". . . . _", ". . . . .", "_ . . . .", "_ _ . . .", "_ _ _ . .", "_ _ _ _ .", "_ _ _ _ _" };

    // Start is called before the first frame update
    void Start()
    {
        repeat = true;
        light = GetComponent<Light>();
        if (flashOnStart)
        {
            StartCoroutine(Flash("72", 0.2f));
        }

    }

    private IEnumerator Flash(string textToConvert, float timeOfDot)
    {
        string textInMorse = "";
        ConvertTextToMorseCode(textToConvert, out textInMorse);
        for (int i = 0; i < textInMorse.Length; i++)
        {
            if (textInMorse[i] == ' ')
            {
                yield return 0;
                yield return new WaitForSeconds(timeOfDot);
            }
            else if (textInMorse[i] == '.')
            {
                light.color = Color.blue;
                yield return 0;
                yield return new WaitForSeconds(timeOfDot);
            }
            else if (textInMorse[i] == '_')
            {
                light.color = Color.red;
                yield return 0;
                yield return new WaitForSeconds(0.8f);
            }
            if (repeat)
            {
                if (i == textInMorse.Length - 1)
                {
                    i = 0;
                }
            }
            light.color = Color.white;
        }
    }
    private void ConvertTextToMorseCode(string textToConvert, out string convertedText)
    {
        convertedText = "";
        textToConvert = textToConvert.ToLower();
        for (int i = 0; i < textToConvert.Length; i++)
        {
            for (short j = 0; j < 37; j++)
            {
                if (textToConvert[i] == letters[j])
                {
                    convertedText += morseLetters[j];
                    convertedText += "   ";
                    break;
                }
            }
        }
    }
}
