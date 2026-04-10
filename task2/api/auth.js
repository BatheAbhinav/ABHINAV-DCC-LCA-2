export default async function handler(req, res) {
  if (req.method !== "POST") {
    return res.status(405).end();
  }

  const { password } = req.body;

  // 🔐 AUTH CHECK
  if (!password || password !== process.env.APP_PASSWORD) {
    return res.status(401).json({
      success: false,
      error: "Unauthorized"
    });
  }

  return res.status(200).json({
    success: true
  });
}