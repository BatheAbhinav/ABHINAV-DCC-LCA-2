import { GoogleGenerativeAI } from "@google/generative-ai";

export default async function handler(req, res) {
  if (req.method !== "POST") {
    return res.status(405).json({ error: "Method not allowed" });
  }

  console.log('API KEY IS PRESENT?: ', !!process.env.GEMINI_API_KEY);

  try {
    const { message } = req.body;
    console.log("Received message:", message);

    const genAI = new GoogleGenerativeAI(process.env.GEMINI_API_KEY);

    const model = genAI.getGenerativeModel({
      model: "gemini-3.1-flash-lite-preview"
    });

    const result = await model.generateContent(message);
    const reply = result.response.text();

    res.status(200).json({ reply });

  } catch (error) {
    console.error(error);
    res.status(500).json({ error: "Something went wrong" });
  }
}