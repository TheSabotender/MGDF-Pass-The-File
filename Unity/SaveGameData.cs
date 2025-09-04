using System;
using System.IO;
using UnityEngine;

[Serializable]
public class SaveGameData
{
    [FormerlySerializedAs("integer_one")]
    public int integer_one;

    [FormerlySerializedAs("integer_two")]
    public int integer_two;

    [FormerlySerializedAs("integer_three")]
    public int integer_three;

    [FormerlySerializedAs("integer_four")]
    public int integer_four;

    [FormerlySerializedAs("float_one")]
    public float float_one;

    [FormerlySerializedAs("float_two")]
    public float float_two;

    [FormerlySerializedAs("float_three")]
    public float float_three;

    [FormerlySerializedAs("vector_one")]
    public Vector3 vector_one;

    [FormerlySerializedAs("vector_two")]
    public Vector3 vector_two;

    public static SaveGameData current;
    
    public static void LoadFromFile(string path)
    {
        current = JsonUtility.FromJson<SaveGameData>(File.ReadAllText(path));
    }

    public static void SaveToFile(string path)
    {
        File.WriteAllText(path, JsonUtility.ToJson(current));
    }
}
